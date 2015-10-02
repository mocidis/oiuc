import QtQuick 1.1
Rectangle {
    id: _ROOT
	width: 1366 
    height: 680
    color: "black"
    property variant appState: QtObject {
        property bool login: false
        property string username: "user"
        property string password: "1234"
    }
    property list<ListModel> models: [ ModelRadios { }, ModelOIUs{ }, ModelGroups { } ]
    property alias main: panelMain
    property alias leftPanel: panelLeft
    property alias rightPanel: panelRight
    PanelTop {
        id: panelTop
        anchors {
            top: parent.top
            left: parent.left
            right: panelRight.right
        }
    }
    PanelLeft {
        id: panelLeft
        panel: panelMain
        width: parent.width * 0.18
        anchors {
            top: panelTop.bottom
            left: parent.left
            bottom: parent.bottom
        }
    }
    PanelMain {
        id: panelMain
        width: parent.width * 0.40
        anchors {
            top: panelTop.bottom
            left: panelLeft.right
            bottom: parent.bottom
            leftMargin: 1
        }
    }
    PanelRight {
        id: panelRight
        anchors {
            top: panelTop.bottom
            right: parent.right
            left: panelMain.right
            bottom: parent.bottom
            leftMargin: 1
        }
        MouseArea {
            anchors.fill: parent
            onClicked: panelRight.log("add one line");
        }
    }
    VirtualKeyboard {
        id: _KEYBOARD
        anchors {
            bottom: parent.bottom
            horizontalCenter: panelMain.horizontalCenter
            bottomMargin: 20
        }
    }
    StateGroup {
        states: [
            State {
                name: "logout"
                when: !appState.login
                PropertyChanges { target: panelLeft; visible: false }
                PropertyChanges { target: panelRight; visible: false }
                PropertyChanges { target: _ROOT; color: "#F0F0F0" }
            },
            State {
                name: "login"
                when: appState.login
                PropertyChanges { target: panelLeft; visible: true }
                PropertyChanges { target: panelRight; visible: true }
                PropertyChanges { target: _ROOT; color: "black" }
            }
        ]
    }
}
