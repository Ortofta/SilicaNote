#include "notemodel.h"

NoteModel::NoteModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QHash<int, QByteArray> NoteModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";
    return roles;
}

int NoteModel::rowCount(const QModelIndex &parent) const {
    return _notes.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const {
    Note* note = _notes.at(index.row());
    if(NoteRoles(role) == TitleRole) {
        return note->getTitle();
    } else {
        return note->getBody();
    }
}

void NoteModel::addNote(Note *note) {
    _notes.append(note);
}

void NoteModel::clearModel() {
    _notes.clear();
}
