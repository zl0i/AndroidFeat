import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import "./components"

Item {


    Column {
        x: parent.width/2 - width/2
        y: 50
        spacing: 25
        Repeater {
            model: [
                {
                    'icon': "qrc:/icons/google.svg",
                    'title': qsTr("Войти с помощью Google"),
                    //'class': _auth
                },
                {
                    'icon': "qrc:/icons/vk.svg",
                    'title': qsTr("Войти с помощью ВКонтакте"),
                    //'class': _auth
                },
                {
                    'icon': "qrc:/icons/yandex.svg",
                    'title': qsTr("Войти с помощью Google"),
                    //'class': _auth
                }
            ]
            delegate: OAuthElement {
                icon: modelData.icon
                text: modelData.title
                //onLogin: modelData.class.googleGrant()
                onRequestUserInfo: {

                }
            }
        }
    }
}
