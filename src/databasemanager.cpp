#include "databasemanager.h"
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
    QSqlQuery query(db);
    query.exec("SELECT OID, remote_id, title, note FROM notes;");
    list.clearNotes();

    while(query.nextResult()) {
        Note *note = new Note();
        note->setRowId(query.value(0).toDouble());
        note->setRemoteId(query.value(1).toDouble());
        note->setTitle(query.value(2).toString());
        note->setBody(query.value(3).toString());
        list.addNote(note);
    }
}
