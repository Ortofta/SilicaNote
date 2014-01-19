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

#include "servercommunicator.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>

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
bool ServerCommunicator::syncNote(Note *note) {
    QByteArray data = toJson(note->getRowId(), note->getTitle(), note->getBody());
    QNetworkRequest request;
    request.setUrl(QUrl("http://sync.silicanote.eu/services/notes/addnote"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = manager->post(request, data);

    if(reply->error() == QNetworkReply::NoError) {
        return true;
    } else {
        return false;
    }
}

QList<Note*> ServerCommunicator::fetchNotes() {
    QList<Note*> list;
    QNetworkRequest request;
    request.setUrl(QUrl("insert host here"));
    QNetworkReply *reply = manager->get(request);
    if(reply->error() == QNetworkReply::NoError) {

    } else {
        return list;
    }
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

QList<Note*> ServerCommunicator::fromJson(QString json) {
    QList<Note*> list;

    return list;
}
