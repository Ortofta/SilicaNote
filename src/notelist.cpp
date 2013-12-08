#include "notelist.h"

NoteList::NoteList(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<Note> NoteList::notes() {

}

void NoteList::addNote(Note *note) {
    _notes.append(note);
}

void NoteList::deleteNote(int index) {

}

void NoteList::clearNotes() {
    _notes.clear();
}

int NoteList::countNotes() {
    return 0;
}

static void clearNotes(QQmlListProperty<Note> *property) {

}

static int notesSize(QQmlListProperty<Note> *property) {
    return 0;
}

static Note* NoteAt(QQmlListProperty<Note> *property, int index) {
    return NULL;
}
