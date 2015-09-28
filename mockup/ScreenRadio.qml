import QtQuick 2.0
ScreenCommon {
//    property alias tName: nametext.text
//    property alias tDesc: desctext.text
//    property int port: -1
    DeviceRadio {
        height: parent.width/2
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 20
        }
    }
}
