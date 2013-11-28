#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "NoteStorage");
    db.setDatabaseName("$HOME/.local/share/Silicanote/NoteStorageDb");
    db.open();
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS notes(remote_id INT UNIQUE, title TEXT, note TEXT)");
}

DatabaseManager::~DatabaseManager() {
    if(db.isOpen()) {
        db.close();
    }
}

double DatabaseManager::storeNote(QString title, QString body) {
    if(!db.isOpen()) {
        return -1;
    }

    QSqlQuery query(db);

    query.prepare("INSERT OR REPLACE INTO notes(title,note) VALUES (?,?)");
    query.bindValue(0, title);
    query.bindValue(1, body);
    query.exec();
    query.clear();
    query.exec("selectlast_insert_rowid()");
    query.first();
    return query.value(0).toDouble();
}

QList<Note*> DatabaseManager::getNotes() {
    QList<Note*> notes;
    return notes;
}
