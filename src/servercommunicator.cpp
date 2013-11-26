#include "servercommunicator.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

/**
 * Constructor - setup everything needed by the class
 * @brief ServerCommunicator::ServerCommunicator
 * @param parent
 */
ServerCommunicator::ServerCommunicator(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

/**
 * Destructor - delete any references used by the class
 * @brief ServerCommunicator::~ServerCommunicator
 */
ServerCommunicator::~ServerCommunicator() {
    delete manager;
}

/**
 *
 * @brief ServerCommunicator::syncNote
 * @param header
 * @param body
 */
void ServerCommunicator::syncNote(const QString id, const QString header, const QString body) {
    QByteArray data = toJson(id, header, body);
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.google.com"));
    manager->post(request, data);
}

QByteArray ServerCommunicator::toJson(const QString id, const QString header, const QString body) {
    QJsonObject obj;
    obj.insert("id", id);
    obj.insert("header", header);
    obj.insert("body", body);
    QJsonDocument document;
    document.setObject(obj);
    return document.toJson();
}

