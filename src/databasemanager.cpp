/*
  Copyright (C) 2013 Markus Svensson.
  Contact: Markus Svensson <markus.svensson@me.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "databasemanager.h"
#include "note.h"
#include <QDir>
#include <QStandardPaths>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    qDebug() << "Data path: " << dataPath;
    createDataDir(dataPath);
    db = QSqlDatabase::addDatabase("QSQLITE", "NoteStorage");
    db.setDatabaseName(dataPath + "/NoteStorageDb");
    db.open();

    if(!isDbOpen()) {
        qDebug() << "Database could not be opened: " << db.lastError();
    }

    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS notes(remote_id INT UNIQUE, title TEXT, note TEXT)");
}

DatabaseManager::~DatabaseManager() {
    if(db.isOpen()) {
        db.close();
    }
}

void DatabaseManager::createDataDir(const QString dataPath) {
    QDir *dir = new QDir();
    if(!dir->exists(dataPath)) {
        bool result = dir->mkdir(dataPath);
        if(!result) {
            qDebug() << "Could not create data directory " << dataPath;
        }
    }
    delete(dir);
}

double DatabaseManager::storeNote(QString title, QString body) {
    if(!isDbOpen()) {
        qDebug() << "Database is not open - no data has been saved";
        return -1;
    }

    QSqlQuery query(db);

    query.prepare("INSERT OR REPLACE INTO notes(title,note) VALUES (?,?)");
    query.bindValue(0, title);
    query.bindValue(1, body);
    query.exec();
    query.clear();
    bool success = query.exec("select last_insert_rowid()");

    if(!success) {
        qDebug() << "Query failed: " << query.lastError();
    }

    query.first();
    return query.value(0).toDouble();
}

bool DatabaseManager::isDbOpen() {
    if(!db.isOpen()) {
        return false;
    }

    return true;
}

void DatabaseManager::getNotes() {
    clearNotes();
    qDebug() << "Getting notes from DB";

    QSqlQuery query(db);
    bool success = query.exec("SELECT OID, remote_id, title, note FROM notes;");

    if(!success) {
        qDebug() << "Query failed: " << query.lastError();
    }

    while(query.next()) {
        Note *note = new Note();
        note->setRowId(query.value(0).toDouble());
        note->setRemoteId(query.value(1).toDouble());
        note->setTitle(query.value(2).toString());
        qDebug() << "Adding note with title: " << query.value(2).toString();
        note->setBody(query.value(3).toString());
        qDebug() << "Adding note with body: " << query.value(3).toString();
        addNote(note);
    }
}

QQmlListProperty<Note> DatabaseManager::notes() {
    qDebug() << "Reading note list property - list lenght:" << _notes.length();
    return QQmlListProperty<Note>(this, &_notes, &append, &size, &at, &clear);
}

void DatabaseManager::addNote(Note *note) {
    qDebug() << "Adding note to list";
    _notes.append(note);
    this->notesChanged();
}

void DatabaseManager::deleteNote(int index) {
    //qDebug() << "Removing note at index " << index;
    _notes.removeAt(index);
    this->notesChanged();
}

void DatabaseManager::clearNotes() {
    //qDebug() << "Clearing note list";
    _notes.clear();
    this->notesChanged();
}

int DatabaseManager::countNotes() {
    //qDebug() << "Reading note list property lenght:" << _notes.length();
    return _notes.length();
}

Note* DatabaseManager::noteAt(int index) {
    //qDebug() << "Reading note at index " << index;
    return _notes.at(index);
}

void DatabaseManager::append(QQmlListProperty<Note> *property, Note* value) {
    DatabaseManager *list = (DatabaseManager*) property;
    list->addNote(value);
    list->notesChanged();
}

void DatabaseManager::clear(QQmlListProperty<Note> *property) {
    DatabaseManager *list = (DatabaseManager*) property;
    list->clearNotes();
    list->notesChanged();
}

int DatabaseManager::size(QQmlListProperty<Note> *property) {
    DatabaseManager *list = (DatabaseManager*) property;
    return list->countNotes();
}

Note* DatabaseManager::at(QQmlListProperty<Note> *property, int index) {
    DatabaseManager *list = (DatabaseManager*) property;
    return list->noteAt(index);
}


