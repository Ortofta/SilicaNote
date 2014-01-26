#include "syncmanager.h"

SyncManager::SyncManager(DatabaseManager *manager, QObject *parent) :
    QObject(parent)
{
    dbManager = manager;
}

SyncManager::~SyncManager() {
    dbManager->deleteLater();
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
