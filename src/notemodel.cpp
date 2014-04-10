/*
  Copyright (C) 2013-2014 Markus Svensson.
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

#include "notemodel.h"
#include <QtDebug>
#include <QVector>


NoteModel::NoteModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QHash<int, QByteArray> NoteModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";
    roles[IdRole] = "rowid";
    return roles;
}

int NoteModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return _notes.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const {
    Note* note = _notes.at(index.row());
    if(NoteRoles(role) == TitleRole) {
        return note->getTitle();
    } else if(NoteRoles(role) == BodyRole){
        return note->getBody();
    } else {
        return note->getRowId();
    }
}

bool NoteModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    Note* note = _notes.at(index.row());
    if(NoteRoles(role) == TitleRole) {
        note->setTitle(value.toString());
        //_notes.replace(index.row(), note);
        emit dataChanged(index, index);
        return true;
    } else if(NoteRoles(role) == BodyRole){
        note->setBody(value.toString());
        QVector<int> * vect = new QVector<int>;
        vect->append(role);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool NoteModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent);
    qDebug() << "NoteModel::insertRows was called";
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        _notes.insert(position, new Note());
    }

    endInsertRows();
    return true;
}

bool NoteModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        _notes.removeAt(position);
    }

    endRemoveRows();
    return true;
}

void NoteModel::addNote(Note *note) {
    beginInsertRows(QModelIndex(), _notes.size(), _notes.size());
    _notes.append(note);
    endInsertRows();
}

QList<Note *> NoteModel::getNotes() {
    return _notes;
}

void NoteModel::clearModel() {
    _notes.clear();
}
