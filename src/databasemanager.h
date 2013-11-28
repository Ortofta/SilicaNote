#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QtSql>
#include <QList>
#include "note.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
    QSqlDatabase db;
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();
signals:

public slots:
    double storeNote(const QString title, const QString body);
    QList<Note*> getNotes();
};

#endif // DATABASEMANAGER_H
