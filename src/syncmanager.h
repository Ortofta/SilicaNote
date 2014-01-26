#ifndef SYNCMANAGER_H
#define SYNCMANAGER_H

#include <QObject>
#include "databasemanager.h"

class SyncManager : public QObject
{
    Q_OBJECT
    DatabaseManager *dbManager;
public:
    explicit SyncManager(QObject *parent = 0);
    void setDbManager(DatabaseManager *manager);
    ~SyncManager();
signals:
    void syncedOk();
    void syncFailed();
    void syncNote(Note* note);
    void deleteNote(double id);
public slots:
    void syncAllNotes();
    void deleteAllNotes();
};

#endif // SYNCMANAGER_H
