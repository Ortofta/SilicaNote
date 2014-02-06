#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
    QSettings _userSettings;
public:
    explicit Settings(QObject *parent = 0);
    //Q_PROPERTY(QString username READ getUserName WRITE setUserName NOTIFY userNameChanged)
    //Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)

    Q_INVOKABLE QString getUserName();
    Q_INVOKABLE QString getPassword();
    Q_INVOKABLE bool isSyncEnabled();
    Q_INVOKABLE void setUserName(QString userName);
    Q_INVOKABLE void setPassword(QString password);
    Q_INVOKABLE void setSyncEnabled(bool isSyncEnabled);

signals:
    void userNameChanged();
    void passwordChanged();
public slots:

};

#endif // SETTINGS_H
