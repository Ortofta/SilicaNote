#include "note.h"

Note::Note(QObject *parent) :
    QObject(parent)
{
}

void Note::setRowId(double rowId) {
    _row_id = rowId;
}

double Note::getRowId() {
    return _row_id;
}

void Note::setRemoteId(double remoteId) {
    _remote_id = remoteId;
}

double Note::getRemoteId() {
    return _remote_id;
}

void Note::setTitle(const QString title) {
    _title = title;
}

QString Note::getTitle() {
    return _title;
}

void Note::setBody(const QString body) {
    _body = body;
}

QString Note::getBody() {
    return _body;
}
