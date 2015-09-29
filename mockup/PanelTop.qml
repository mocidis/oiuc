import QtQuick 2.0

PanelCommon {
    id: root
    height: 45
    color: "#F0F0F0"
    Flow {
        id: menu
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
            //margins: 15
        }
        spacing: 30
        PushButton {
            color: "transparent"
            width: 90
            height: root.height
            Text {
                anchors.centerIn: parent
                text: "About"
            }
        }
        PushButton {
            color: "transparent"
            width: 90
            height: root.height
            Text {
                anchors.centerIn: parent
                text: "Settings"
            }
        }
        PushButton {
            color: "transparent"
            width: 90
            height: root.height
            Text {
                anchors.centerIn: parent
                text: "PSTN"
            }
        }
        PushButton {
            color: "transparent"
            width: 90
            height: root.height
            Text {
                anchors.centerIn: parent
                text: "Group Config"
            }
        }
    }
    Text {
        id: time
        anchors {
            top: parent.top
            right: parent.right
            bottom: parent.bottom
            margins: 15
        }
        text: "--/--/--"
        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: parent.text = Qt.formatDateTime(new Date(), "hh:mm:ss -- dd/MM/yyyy")
        }
    }
    Rectangle {
        height: 1
        color: "black"
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
