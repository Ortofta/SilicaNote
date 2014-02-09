import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id:settings
    onDone: {
        if (result === DialogResult.Accepted) {
            userSettings.setPassword(password.text);
            userSettings.setUserName(username.text);
            userSettings.setSyncEnabled(sync.checked);
        }
    }

    Column {
        id: column
        y: 100
        width: parent.width
        spacing: 20

        TextField {
            id: username
            width: 480
            height: 100
            text: userSettings.getUserName()
            placeholderText: "Username"
            label: "Username"
        }

        TextField {
            id: password
            width: 480
            height: 100
            text: userSettings.getPassword()
            placeholderText: "Password"
            label: "Password"
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
    }
}



