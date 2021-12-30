import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Column {
    id: _item

    height: 50
    spacing: 10

    property string text: ""
    property string icon: ""

    signal login()
    signal requestUserInfo()

    Row {
        height: 50
        spacing: 10
        Label {
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: _item.text
        }
        Rectangle {
            width: 50
            height: 50
            radius: 25
            color: "#FFFFFF"
            Image {
                anchors { fill: parent; margins: 8 }
                fillMode: Image.PreserveAspectFit
                antialiasing: true
                mipmap: true
                smooth: true
                source: _item.icon
            }
            MouseArea {
                id: _mouseArea
                anchors.fill: parent
                onClicked: _item.login()
            }
            layer.enabled: true
            layer.effect: DropShadow {
                radius: _mouseArea.pressed ? 6 : 8
                samples: 16
                color: "#80000000"
            }
        }
    }
}
