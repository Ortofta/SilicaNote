#ifndef NOTELIST_H
#define NOTELIST_H

#include <QObject>
#include <QQmlListProperty>
#include <QList>
#include "note.h"

class NoteList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Note> notes READ notes)
private:
    QList<Note *> _notes;
public:
    explicit NoteList(QObject *parent = 0);
    QQmlListProperty<Note> notes();
    Q_INVOKABLE void addNote(Note *note);
    Q_INVOKABLE void deleteNote(int index);
    Q_INVOKABLE int countNotes();
    Q_INVOKABLE void clearNotes();

    static void clearNotes(QQmlListProperty<Note> *property);
    static int notesSize(QQmlListProperty<Note> *property);
    static Note* noteAt(QQmlListProperty<Note> *property, int index);
signals:

public slots:

};

#endif // NOTELIST_H
