import QtQuick 1.1
Rectangle {
    id: _ROOT
	width: 1280
    height: 680
    color: "black"
    property list<ListModel> models: [ ModelRadios{}, ModelOIUs{}, ModelGroups{} ]
    property variant appState: QtObject {
        property bool login: true
        //property bool login: pstn.isLoggedIn()
    }
	/*Connections {
		target: pstn
		onLoggedInChange: {
			appState.login = pstn.isLoggedIn();
		}
	}*/
    property alias main: panelMain
    property alias leftPanel: panelLeft
    property alias rightPanel: panelRight
	property variant radios : _ROOT.models[0]
	property variant oius: _ROOT.models[1]
	property variant groups: _ROOT.models[2]
	Connections {
		target: radioObj 
		onUpdateRadioManager: {
			if (mIndex == -1) {
				radios.append({
					"name": name, 
					"status": status, 
					"frequency":frequency, 
					"location": location, 
					"port_mip": port_mip, 
					"downtime":downtime,
					"avaiable":avaiable,
					"port":port, 
					"description":desc,
					"iState": 0
				});
			} else {
				radios.setProperty(mIndex,"name", name);
				radios.setProperty(mIndex,"status", status);
				radios.setProperty(mIndex,"frequency", frequency);
				radios.setProperty(mIndex,"location", location);
				radios.setProperty(mIndex,"port_mip", port_mip);
				radios.setProperty(mIndex,"downtime", downtime);
				radios.setProperty(mIndex,"avaiable", avaiable);
				radios.setProperty(mIndex,"port", port);
				radios.setProperty(mIndex,"description", desc);
			}
		}
	}
	Connections {
		target: oiucObj
		onUpdateOIUCManager: {
			if (mIndex == -1) {
				oius.append({
					"type": type, 
					"name": name, 
					"status":status, 
					"downtime":downtime, 
					"description":desc,
					"iState": 0
				});
			} else {
				oius.setProperty(mIndex, "type", type);
				oius.setProperty(mIndex, "name", name);
				oius.setProperty(mIndex, "status", status);
				oius.setProperty(mIndex, "downtime", downtime);
				oius.setProperty(mIndex, "description", desc);
			}
		}
	}
	Connections {
		target: groupObj
		onGroupAdded: {
			groups.append({
				"name": name, 
				"description": desc,
				"nodes": [
					{
						"modelIdx": 0,
						"itemIdx": 0,
					}, 
				],
                "iState": 0
			});
			groups.get(currentIdx).nodes.set(0,{
                "modelIdx": 0, 
                "itemIdx": itemIdx[0]
            });
			for (var i=1;i<itemIdx.length;i++) {
				groups.get(currentIdx).nodes.append({
                        "modelIdx": 0, 
                        "itemIdx": itemIdx[i]
                });
			}
		}
        onGroupDeleted: {
            console.log("group deleted");
            groups.remove(currentIdx);
        }
	}
	Connections {
		target: pstn
		onCallingState: {
            _CALLDIALOG.text = msg;
	/*
	0 PJSIP_INV_STATE_NULL 	Before INVITE is sent or received 
	1 PJSIP_INV_STATE_CALLING 	After INVITE is sent
	2 PJSIP_INV_STATE_INCOMING 	After INVITE is received.
	3 PJSIP_INV_STATE_EARLY 	After response with To tag.
	4 PJSIP_INV_STATE_CONNECTING 	After 2xx is sent/received.
	5 PJSIP_INV_STATE_CONFIRMED 	After ACK is sent/received.
	6 PJSIP_INV_STATE_DISCONNECTED 	Session is terminated. 
	*/
   			if (st_code == -1) {
				_CALLDIALOG.dialogState = 2; 
			} else if ( st_code == 0) {
				_CALLDIALOG.dialogState	= 0;
			} else if (st_code == 1) {
				_CALLDIALOG.dialogState	= 1;
			} else if (st_code == 2) {
				_CALLDIALOG.dialogState = 2;	
			} else if (st_code == 5) {
				_CALLDIALOG.dialogState = 3;
			} else if (st_code == 6) {
				_CALLDIALOG.dialogState = 0;	
			}
        }
	}
	FontLoader {id: lcdFont; source: "../static/fonts/digital-7 (mono).ttf"}
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
					return parent.height - 20
				}else {
					return ( 100 * (Math.ceil(radios.count/2) + Math.ceil(oius.count/2) + Math.ceil(groups.count/2)) + 120)
				}
			}
			clip: true
		}
		ScrollBar {
			scrollArea: panelLeft
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
    TelephoneKeyboard {
        id: _TELKB
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: panelMain.horizontalCenter
        }
        visible: false
    }
    CallDialog {
        id:_CALLDIALOG
        width: 450
        height: 180
        anchors {
            horizontalCenter: panelMain.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        visible: true
    }
    GroupManDialog {
        id:_GMDIALOG
        width: 300
        height: 500
        anchors {
            horizontalCenter: panelMain.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        visible: false
    }
    VirtualKeyboard {
        id: _KEYBOARD
        anchors {
            bottom: parent.bottom
            horizontalCenter: panelMain.horizontalCenter
            bottomMargin: 20
        }
        visible: false
    }
    MySlider {
        id: _SLIDER
        width: 200
        height: 50
        fontSize: 16
        anchors {
            top: panelTop.bottom
            right: panelTop.right
            rightMargin: (object == null) ? 0:object.anchors.rightMargin
        }
        visible: object != null
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
/*
    StateGroup {
        states: [
            State {
                name: "telkbVisible"
                when: _TELKB.visible
                PropertyChanges { target: panelLeft; enabled: false}
                PropertyChanges { target: panelRight; enabled: false}
                PropertyChanges { target: panelMain; enabled: false}
                PropertyChanges { target: panelTop; enabled: false}
            },
            State {
                name: "telkbInvisible"
                when: !_TELKB.visible
                PropertyChanges { target: panelLeft; enabled: true}
                PropertyChanges { target: panelRight; enabled: true}
                PropertyChanges { target: panelMain; enabled: true}
                PropertyChanges { target: panelTop; enabled: true}
            }
        ]
    }
*/
}
