#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QtSql>
#include <QList>
#include <QQmlEngine>
#include <QJSEngine>
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

// Second, define the singleton type provider function (callback).
static QObject *databaseManagerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    DatabaseManager *manger = new DatabaseManager();
    return manger;
}

#endif // DATABASEMANAGER_H
