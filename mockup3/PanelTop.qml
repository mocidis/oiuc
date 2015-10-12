import QtQuick 1.1

PanelCommon {
    property int itemWidth: 120
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
        spacing: 5
        PushButton {
            color: "transparent"
            width: home.width + 60
            height: root.height
            Text {
                id: home
                anchors.centerIn: parent
                text: "Home"
            }
            onClicked: {
                //_ROOT.main.hShow(-1, 0);
                if (_ROOT.leftPanel.current != null) {
                    _ROOT.leftPanel.current.toggleControlled();
                    _ROOT.leftPanel.current = null;
                }
            }
        }
        PushButton {
            color: "transparent"
            width: pstn.width + 60
            height: root.height
            Text {
                id: pstn
                anchors.centerIn: parent
                text: "Telephone"
            }
            onClicked: { 
                //_ROOT.main.hShow(-1, 0);
                if (_ROOT.leftPanel.current != null) {
                    _ROOT.leftPanel.current.toggleControlled();
                    _ROOT.leftPanel.current = null;
                }
                _TELKB.visible = !_TELKB.visible;
            }
        }
        PushButton {
            color: "transparent"
            width: manageGroups.width + 60
            height: root.height
            Text {
                id: manageGroups
                anchors.centerIn: parent
                text: "Create groups"
            }
            onClicked: {
                //_ROOT.main.hShow(-1, 1);
                _GMDIALOG.visible = true;
                if (_ROOT.leftPanel.current != null) {
                    _ROOT.leftPanel.current.toggleControlled();
                    _ROOT.leftPanel.current = null;
                }
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
		font {
            family: lcdFont.name
		    pixelSize: 16 
		    letterSpacing: 3
        }
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
    StateGroup {
        states: [
            State {
                name: "logout"
                when: !_ROOT.appState.login || _TELKB.visible || _GMDIALOG.visible
                PropertyChanges { target: menu; enabled: false }
            },
            State {
                name: "login"
                when: _ROOT.appState.login && !_TELKB.visible && !_GMDIALOG.visible
                PropertyChanges { target: menu; enabled: true }
            }
        ]
    }
}
