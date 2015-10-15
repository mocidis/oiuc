import QtQuick 1.1
ScreenCommon {
    property alias oModelItem: oiu.oModelItem
    visible: oModelItem.iState == 2
    DeviceOIUC {
		id: oiu
        height: parent.width/2
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            //margins: 20
        }
    }
}
