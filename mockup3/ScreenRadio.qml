import QtQuick 1.1
ScreenCommon {
    property alias oModelItem: radio.oModelItem
    visible: oModelItem.iState == 2
    DeviceRadio {
        id: radio
        height: parent.width/2
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            //margins: 20
        }
    }
}
