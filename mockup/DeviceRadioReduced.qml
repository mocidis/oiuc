import QtQuick 2.0

Rectangle {
    property alias oModelItem: indicator.oModelItem
    height: 60
    width: parent.width
    Flow {
        flow: Flow.TopToBottom
        spacing: 3
        anchors {
            left: parent.left
            right: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            leftMargin: 8
        }
        Text {
            width: parent.width
            color: "white"
            text: oModelItem.name + "." + oModelItem.port
        }
        Text {
            width: parent.width
            color: "white"
            text: oModelItem.description
        }
    }
    TriLEDFull {
        id: indicator
        anchors {
            right: parent.right
            left: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        columnFormat: false
        dimColor: "lightgray"
    }
}
