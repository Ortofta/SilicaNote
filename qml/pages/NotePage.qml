import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: notepage

    PageHeader {
        title: "Create Note"
    }
    SilicaFlickable {
        anchors.fill: parent
        anchors.topMargin: 150
            contentHeight: column.height
            Column {
                id: column
                width: parent.width
                spacing: 20

                Label {
                     color: theme.highlightColor
                     font.family: theme.fontFamilyHeading
                     text: "Title:"
                 }

                TextField {
                    id: notetitle
                     width: 480
                     height: 30
                     placeholderText: "Note title"
                 }

                Label {
                     color: theme.highlightColor
                     font.family: theme.fontFamilyHeading
                     text: "Note:"
                 }

                TextArea {
                    id: notetext
                    width: 480
                    height: 300
                     placeholderText: "Enter text here!"
                }

                Button {
                    text: "Save"
                    onClicked: {
                        Storage.writeNote(notetitle.text, notetext.text)
                        pageStack.pop()
                    }
                }
            }
    }
}
