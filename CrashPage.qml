import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {


    Button {
        anchors.centerIn: parent
        text: "Crash"
        onClicked: _appCore.crash()
    }
}
