#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "note.h"

class NoteModel : public QAbstractListModel
{
    Q_OBJECT
    QList<Note *> _notes;
public:
    explicit NoteModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void addNote(Note *note);
    void clearModel();

    enum NoteRoles {
            TitleRole = Qt::UserRole + 1,
            BodyRole
    };

signals:

public slots:

};

#endif // NOTEMODEL_H
