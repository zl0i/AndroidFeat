import QtQuick 2.15
import QtQuick.Controls 2.15


import "./qml/components"

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    background: Rectangle { color: "#292929" }

    SwipeView {
        id: _swipe
        anchors.fill: parent
        PushPage {

        }
        CrashPage {

        }
    }

    PageIndicator {
        x: parent.width/2 - width/2
        y: parent.height-30
        count: _swipe.count
        currentIndex: _swipe.currentIndex
    }

    Component.onCompleted: {
        if(_deepLinks.getLink().length > 0)
            _linkPopup.show(_deepLinks.getLink())
    }

    LinkPopup {
        id: _linkPopup
    }
}
