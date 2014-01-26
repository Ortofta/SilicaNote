#include "syncmanager.h"

SyncManager::SyncManager(QObject *parent) : QObject(parent) {

}

SyncManager::~SyncManager() {
    dbManager->deleteLater();
}

void SyncManager::setDbManager(DatabaseManager *manager){
    dbManager = manager;
}

void SyncManager::syncAllNotes() {
    QList<Note*> notes = dbManager->getModel()->getNotes();
    for(int i = 0; i < notes.length(); i++) {
        emit syncNote(notes.at(i));
    }
}

void SyncManager::deleteAllNotes() {
    QList<Note*> notes = dbManager->getModel()->getNotes();
    for(int i = 0; i < notes.length(); i++) {
        emit deleteNote(notes.at(i)->getRemoteId());
    }
}
