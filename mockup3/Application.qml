import QtQuick 1.1
Rectangle {
    id: _ROOT
	width: 1360
    height: 680
    color: "black"
    property list<ListModel> models: [ ModelRadios{}, ModelOIUs{}, ModelGroups{} ]
    property variant appState: QtObject {
        //property bool login: false
        property bool login: true
        property string username: "user"
        property string password: "1234"
    }
    property alias main: panelMain
    property alias leftPanel: panelLeft
    property alias rightPanel: panelRight
	property variant radios : _ROOT.models[0]
	property variant oius: _ROOT.models[1]
	property variant groups: _ROOT.models[2]
	Connections {
		target: radioObj 
		onUpdateRadioManager: {
			radios.append({"name": name, "status": status, "frequency":frequency, "location": location, "port_mip":port_mip, "downtime":downtime,"avaiable":avaiable,"port":port});
		}
	}
	Connections {
		target: oiucObj
		onUpdateOIUCManager: {
			oius.append({"type": type, "name": name, "status":status, "downtime":downtime});
		}
	}
	Connections {
		target: groupObj
		onUpdateGroupManager: {
			groups.append({
				"name": name, 
				"description": "ABC DEF",
				"nodes": [
					{
						"modelIdx": 0,
						"itemIdx": 0
					}
				]
			});
		}
	}
    PanelTop {
        id: panelTop
        anchors {
            top: parent.top
            left: parent.left
            right: panelRight.right
        }
    }
	Rectangle {
		id: rcPanelLeft
		width: parent.width * 0.18
		color: "#F0F0F0"
		anchors {
			top: panelTop.bottom
			left: parent.left
			bottom: parent.bottom
		}
		PanelLeft {
			id: panelLeft
			panel: panelMain
			width: parent.width 
			anchors {
				top: parent.top
				left: parent.left
				bottom: parent.bottom
			}
			contentHeight: {
				if ((100 * (Math.ceil(radios.count/2) + Math.ceil(oius.count/2) + Math.ceil(groups.count/2)) + 120) < parent.height) {
					console.log("hihihi: " + parent.height);
					return parent.height - 20
				}else {
					console.log("hehehehe");
					return ( 100 * (Math.ceil(radios.count/2) + Math.ceil(oius.count/2) + Math.ceil(groups.count/2)) + 120)
				}
			}
			clip: true
		}
		ScrollBar {
			scrollArea: panelLeft; width: 8
			anchors { right: panelLeft.right; bottom: panelLeft.bottom ; top: panelLeft.top}
		}
	}
    PanelMain {
        id: panelMain
        width: parent.width * 0.4
        anchors {
            top: panelTop.bottom
            left: rcPanelLeft.right
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
