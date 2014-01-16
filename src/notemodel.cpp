#include "notemodel.h"
#include <QtDebug>


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
    Q_UNUSED(parent);

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

bool NoteModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent);
    qDebug() << "NoteModel::insertRows was called";
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        _notes.insert(position, new Note());
    }

    endInsertRows();
    return true;
}

bool NoteModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        _notes.removeAt(position);
    }

    endRemoveRows();
    return true;
}

void NoteModel::addNote(Note *note) {
    beginInsertRows(QModelIndex(), _notes.size(), _notes.size());
    _notes.append(note);
    endInsertRows();
}

void NoteModel::clearModel() {
    _notes.clear();
}
