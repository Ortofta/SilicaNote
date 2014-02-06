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
                text: userSettings.username
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
                text: userSettings.password
                placeholderText: "Password"
                echoMode: TextInput.PasswordEchoOnEdit
            }
            Button {
                text: "Save"
                onClicked: {
                    userSettings.setPassword(password.text);
                    userSettings.setUserName(username.text);
                    pageStack.pop();
                }
            }
        }
    }
}


