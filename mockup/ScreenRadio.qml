import QtQuick 2.0
ScreenCommon {
    property alias oModelItem: radio.oModelItem
    DeviceRadio {
        id: radio
        height: parent.width/2
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 20
        }
    }
}
