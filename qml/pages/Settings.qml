import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id:settings

    PageHeader {
        title: "Settings"
    }
    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        anchors.topMargin: 150
        contentHeight: column.height

        Column {
            id: column
            anchors.topMargin: 150
            width: parent.width
            spacing: 20

            Label {
                color: Theme.highlightColor
                font.family: Theme.fontFamilyHeading
                text: "Username:"
            }

            TextField {
                id: username
                width: 480
                height: 50
                text: userSettings.getUserName()
                placeholderText: "Username"
            }

            Label {
                color: Theme.highlightColor
                font.family: Theme.fontFamilyHeading
                text: "Password:"
            }
            TextField {
                id: password
                width: 480
                height: 50
                text: userSettings.getPassword()
                placeholderText: "Password"
                echoMode: TextInput.PasswordEchoOnEdit
            }
            Label{
                color: Theme.highlightColor
                font.family: Theme.fontFamilyHeading
                text: "Enable sync:"
            }

            Switch {
                id: sync
                checked: userSettings.isSyncEnabled()
            }
            Button {
                text: "Save"
                onClicked: {
                    userSettings.setPassword(password.text);
                    userSettings.setUserName(username.text);
                    userSettings.setSyncEnabled(sync.checked);
                    pageStack.pop();
                }
            }
        }
    }
}


