import QtQuick 1.1
import Sailfish.Silica 1.0

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
            model: 10
            delegate: BackgroundItem {
                width: ListView.view.width
                onClicked: console.log("clicked!")
                Label {
                    text: "Note"
                }
            }
        }

    }
}
