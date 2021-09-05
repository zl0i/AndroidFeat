import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {

    property var pushModel: _notify.getDataPush()

    Connections {
        target: _notify
        function onSendingMessage() {
            pushModel.push(data)
            console.log(JSON.stringify(pushModel))
            pushModelChanged()
        }
    }

    Row {
        x: parent.width/2 - width/2
        y: 20
        Button {
            text: "Push"
            onClicked: _notify.sendNotification("Title", "Body")
        }

        Button {
            text: "Crash"
            onClicked: _appCore.crash()
        }
    }

    ListView {
        x: 20
        y: 100
        width: parent.width-40
        height: parent.height-y
        model: pushModel
        spacing: 15
        delegate: Label {
            width: parent.width
            color: "#FFFFFF"
            wrapMode: Text.WrapAnywhere
            text: JSON.stringify(modelData)
        }
    }
}
