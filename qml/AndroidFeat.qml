import QtQuick 2.12
import QtQuick.Controls 2.12

import "./components"

Item {

    Row {
        x: 20
        y: 20
        spacing: 20
        TextField {
            id: _urlField
            width: 150
            height: 40
            text: "https://zloi.space"
        }
        Button {
            text: qsTr("Open Chrome Tabs")
            onClicked: _tabs.openChromeTabs(_urlField.text)
        }
    }


}
