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

}

void SyncManager::deleteAllNotes() {

}
