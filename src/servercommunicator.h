#ifndef SERVERCOMMUNICATOR_H
#define SERVERCOMMUNICATOR_H

#include <QObject>
#include <QNetworkAccessManager>

class ServerCommunicator : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;

    QByteArray toJson(const QString id, const QString header, const QString body);
public:
    explicit ServerCommunicator(QObject *parent = 0);
    ~ServerCommunicator();
signals:

public slots:
    void syncNote(const QString id, const QString header, const QString body);
};

#endif // SERVERCOMMUNICATOR_H
