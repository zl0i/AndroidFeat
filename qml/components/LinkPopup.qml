import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: _linkPopup
    parent: Overlay.overlay
    x: 30
    y: parent.height/2 - height/2

    width: parent.width-60
    height: _label.contentHeight+70
    modal: true; dim: true
    padding: 20

    Overlay.modal: Rectangle {
        color: "#80000000"
    }

    function show(link) {
        _label.text = link
        open()
    }


    background: Rectangle {
        radius: 10
        color: "#FFFFFF"
    }

    contentItem: Column {
        id: _column
        spacing: 10
        Label {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            color: "#1A1A1A"
            font { pixelSize: 18; bold: true }
            text: qsTr("App opened from deep link:")
        }

        Label {
            id: _label
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WrapAnywhere
            color: "#1A1A1A"
        }
    }
}
