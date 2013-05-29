import QtQuick 1.1
import Sailfish.Silica 1.0
import "js/storage.js" as Storage

Page {
    id:page

    Column {
        width: page.width
        spacing: theme.paddingLarge
        PageHeader {
            title: "Notes"
        }
        Button {
            text: "New note"
            onClicked: console.log("Add note")
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
        Storage.initialize();
        var loadedNotes = Storage.getNotes();
        for(i = 0; i < loadedNotes.length; i++) {
            notes.append({text:loadedNotes[i].text});
        }
    }
}
