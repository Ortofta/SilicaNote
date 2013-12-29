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

#include "notelist.h"

NoteList::NoteList(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<Note> NoteList::notes() {
    return QQmlListProperty<Note>(this, &_notes, &append,
                                             &size,
                                             &at,
                                             &clear);
}

void NoteList::addNote(Note *note) {
    _notes.append(note);
}

void NoteList::deleteNote(int index) {
    _notes.removeAt(index);
}

void NoteList::clearNotes() {
    _notes.clear();
}

int NoteList::countNotes() {
    return _notes.length();
}

Note* NoteList::noteAt(int index) {
    return _notes.at(index);
}

static void append(QQmlListProperty<Note> *property, Note* value) {
    NoteList *list = (NoteList*) property;
    list->addNote(value);
}

static void clear(QQmlListProperty<Note> *property) {
    NoteList *list = (NoteList*) property;
    list->clearNotes();
}

static int size(QQmlListProperty<Note> *property) {
    NoteList *list = (NoteList*) property;
    return list->countNotes();
}

static Note* at(QQmlListProperty<Note> *property, int index) {
    NoteList *list = (NoteList*) property;
    return list->noteAt(index);
}
