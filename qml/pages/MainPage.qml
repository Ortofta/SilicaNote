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
import Sailfish.Silica 1.0
import org.silicanote.notelist.note 1.0

Page {
    id:mainpage

    SilicaListView {
        id:listView
        width: mainpage.width
        height: mainpage.height
        anchors.top: parent.top
        model:noteModel
        header: PageHeader { title: "SilicaNote" }
        VerticalScrollDecorator {}
        //ViewPlaceholder {
        //    id: test
        //    enabled:  noteModel.count() === 0
        //    text: qsTr("You have no notes")
        //}
        delegate: ListItem {
            id: listItem
            width: ListView.view.width
            height: Theme.itemSizeSmall
            anchors {
                left: parent.left
                right: parent.right
                margins: Theme.paddingLarge
            }
            Label {
                id: label
                text: title
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("NotePage.qml"), {note_id:rowid, note_title:title, note_content:body})
                }
            }
        }
        PullDownMenu {
            MenuItem {
                text: "About"
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem {
                text: "Settings"
                onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
            }
            MenuItem {
                text: "Sync All Notes"
                visible: userSettings.isSyncEnabled()
                onClicked:{
                    syncManager.deleteAllNotes();
                    syncManager.syncAllNotes();
                }
            }
            MenuItem {
                text: "New Note"
                onClicked: pageStack.push(Qt.resolvedUrl("NotePage.qml"))
            }
        }
    }
}

