#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QtSql>
#include <QQmlListProperty>
#include <QList>
#include <QQmlEngine>
#include <QJSEngine>
#include "note.h"
#include "notelist.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
    QSqlDatabase db;
    NoteList list;
    bool isDbOpen();
    void createDataDir(const QString dataPath);

public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

signals:

public slots:
    double storeNote(const QString title, const QString body);
    void getNotes();
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
