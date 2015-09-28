import QtQuick 2.0

PanelCommon {
    height: menu.height + 30
    color: "#F0F0F0"
    Flow {
        id: menu
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
            margins: 15
        }
        spacing: 30
        Text {
            text: "About"
        }
        Text {
            text: "Settings"
        }
        Text {
            text: "PSTN"
        }
        Text {
            text: "Group Config"
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
