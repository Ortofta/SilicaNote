#include "settings.h"
#include <QtDebug>

Settings::Settings(QObject *parent) :
    QObject(parent)
{
}

QString Settings::getUserName() {
    qDebug() << "Getting user name";
    return _userSettings.value("username", "Username").toString();
}

QString Settings::getPassword() {
    qDebug() << "Getting password";
    return _userSettings.value("password", "Password").toString();
}

void Settings::setUserName(QString userName) {
    qDebug() << "Setting user name";
    return _userSettings.setValue("username", userName);
}

void Settings::setPassword(QString password) {
    qDebug() << "Setting password";
    return _userSettings.setValue("password", password);
}
