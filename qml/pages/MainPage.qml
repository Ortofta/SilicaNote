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

import QtQuick 2.0
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0

Page {
    id:mainpage

    Column {
        width: page.width
        spacing: theme.paddingLarge
        PageHeader {
            title: "Notes"
        }
        Button {
            text: "New note"
            onClicked: pageStack.push(Qt.resolvedUrl("NotePage.qml"))
        }
        SilicaGridView {
            width: page.width; height:page.height
            model: notes
            delegate: BackgroundItem {
                width: ListView.view.width
                onClicked: console.log("clicked!")
                Label {
                    text: text
                }
            }
        }
        ListModel {
            id:notes
        }

    }
    Component.onCompleted: {
        // Get all notes from the database
        function getNotes(db) {
            var res = [];
            db.transaction(function(tx) {
                var res = tx.executeSql('SELECT * FROM notes');
            });

            return res;
        }

        var db = LocalStorage.openDatabaseSync("SilicaNote", "1.0", "NoteStorageDatabase", 100000, this);
        db.transaction(
            function(tx) {
                tx.executeSql('CREATE TABLE IF NOT EXISTS notes(id INT UNIQUE, title TEXT, note TEXT)');
          });

        console.log("Pagestack depth " + pageStack.depth);
        var loadedNotes = getNotes(db);
        var i;
        for(i = 0; i < loadedNotes.length; i++) {
            notes.append({text:loadedNotes[i].text});
        }
    }
}

