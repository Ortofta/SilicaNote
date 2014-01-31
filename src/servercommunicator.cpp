/*
  Copyright (C) 2013 Markus Svensson.
  Contact: Markus Svensson <markus.svensson@me.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QtDebug>
#include "servercommunicator.h"

/**
 * Constructor - setup everything needed by the class
 * @brief ServerCommunicator::ServerCommunicator
 * @param parent
 */
ServerCommunicator::ServerCommunicator(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(requestFinished(QNetworkReply*)));
    QObject::connect(manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)));

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
void ServerCommunicator::syncNote(Note *note) {
    QByteArray data = toJson(note->getRowId(), note->getTitle(), note->getBody());
    QNetworkRequest request;
    request.setUrl(QUrl("http://sync.silicanote.eu/services/notes/addnote"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    manager->post(request, data);
}

/**
 * @brief ServerCommunicator::fetchNotes
 */
void ServerCommunicator::fetchNotes() {
    QNetworkRequest request;
    request.setUrl(QUrl("http://sync.silicanote.eu/services/notes/getnotes"));
    manager->get(request);
}

/**
 * @brief ServerCommunicator::fetchNote
 * @param id
 * @return
 */
void ServerCommunicator::fetchNote(double id) {
    QNetworkRequest request;
    QString url = "http://sync.silicanote.eu/services/notes/getnote/";
    url.append(QString::number(id));
    request.setUrl(QUrl(url));
    manager->get(request);
}

/**
 * @brief ServerCommunicator::deleteNote
 * @param id
 * @return
 */
void ServerCommunicator::deleteNote(double id) {
    QNetworkRequest request;
    QString url = "http://sync.silicanote.eu/services/notes/deletenote/";
    url.append(QString::number(id));
    request.setUrl(QUrl(url));
    manager->deleteResource(request);
}

/**
 * @brief ServerCommunicator::requestFinished
 * @param reply
 */
void ServerCommunicator::requestFinished(QNetworkReply *reply) {
    if(reply->operation() == QNetworkAccessManager::GetOperation) {
        QByteArray data = reply->readAll();
        if(data.length() == 0) {
            return;
        }

        QList<Note*> notes = fromJson(data);
        for(int i = 0; i < notes.length(); i++) {
            emit noteFetched(notes.at(i));
        }
    }

    reply->deleteLater();
}

void ServerCommunicator::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);
    qDebug() << "Authentication required";
    authenticator->setUser("test");
    authenticator->setPassword("test");
}

QByteArray ServerCommunicator::toJson(const double id, const QString header, const QString body) {
    QJsonObject obj;
    obj.insert("id", id);
    obj.insert("heading", header);
    obj.insert("body", body);
    QJsonDocument document;
    document.setObject(obj);
    return document.toJson();
}

QList<Note*> ServerCommunicator::fromJson(QByteArray json) {
    QJsonDocument document = QJsonDocument::fromJson(json);
    QList<Note*> notes;
    // handle an array of notes
    if(document.isArray()) {
        QJsonArray array = document.array();
        for(int i = 0; i < array.size(); i++) {
           QJsonValue value = array.at(i);
           if(value.isObject()) {
               QJsonObject obj = value.toObject();
               Note *note = new Note(obj.value("heading").toString(), obj.value("body").toString());
               note->setRemoteId(obj.value("id").toDouble());
               notes.append(note);
           }
        }
    } else {
        QJsonObject obj = document.object();
        Note *note = new Note(obj.value("heading").toString(), obj.value("body").toString());
        note->setRemoteId(obj.value("id").toDouble());
        notes.append(note);
    }

    return notes;
}
