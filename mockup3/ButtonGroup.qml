import QtQuick 1.1

Rectangle {
    property alias text: intext.text
    property variant panel: null
    property int tabIndex: -1
    property int modelIndex: -1
    property alias oModelItem: indicator.oModelItem
	//property int mType
    
    signal clicked(int modelIndex, int tabIndex, int iState)

    id: root
    
    width: 80
    height: width
    radius: 10

    function toggleActive() {
        if(oModelItem.iState < 2) oModelItem.iState = ( oModelItem.iState + 1 ) % 2;
        else return;
    }
    function toggleControlled() {
        if (oModelItem.iState == 1) oModelItem.iState = 2;
        else if (oModelItem.iState == 2) oModelItem.iState = 1;
        else return;
    }
    Rectangle {
        anchors {
            fill: parent
            topMargin: 25
            bottomMargin: 25
        }
        color: "transparent"

        Rectangle {
            id: inner
            width: intext.width + 10
            height: intext.height + 5
            border {
                width: 2
                color: "black"
            }

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
            }
           
            Text {
                id: intext
                anchors {
                    centerIn: parent
                }
                horizontalAlignment: Text.AlignHCenter
            }
        }
        TriLED {
            id: indicator
			fullLed: 2
            anchors {
                horizontalCenter:parent.horizontalCenter
                bottom: parent.bottom
            }
            itemWidth: 5
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (oModelItem.iState < 1) return;
            parent.toggleControlled();
            parent.clicked(modelIndex, tabIndex, oModelItem.iState);
/*            if (panel != null) {
                if (oModelItem.iState > 1)
                    panel.hShow(modelIndex, tabIndex);
                else {
                    panel.hShow(-1, 0);
                }
            }
            else {
                console.log("Please bind panel and tabIndex properties to correct values");
            }*/
        }
        onPressAndHold: oModelItem.iState = (oModelItem.iState < 2)?( oModelItem.iState + 1 ) % 2 : oModelItem.iState
    }

	StateGroup {
		state: "inactive"

		states: [
			State {
				name: "inactive"
				when: oModelItem.iState == 0
				PropertyChanges {target: root; color: "lightgray"}
                PropertyChanges {target: inner; color: "white"; border.color: "lightgray" }
                PropertyChanges {target: intext; color: "lightgray" }
			}, 
			State {
				name: "active"
				when: oModelItem.iState == 1
				PropertyChanges {target: root; color: "lightgray"}
                PropertyChanges {target: inner; color: "white"; border.color: "black"}
                PropertyChanges {target: intext; color: "black" }
			},
			State {
				name: "controlled"
				when: oModelItem.iState == 2
				PropertyChanges {target: root; color: "gray"}
                PropertyChanges {target: inner; color: "black" }
                PropertyChanges {target: intext; color: "white" }
                PropertyChanges {target: indicator; dimColor: "lightgray"}
			}
		]

		/*transitions: [
			Transition {
				from: "*"; to: "*"
				ColorAnimation {targets: [root, inner, inner.border, intext]; properties: "color"; duration: 100}
			}
		]*/
	}
    StateGroup {
        states: [
            State {
                name: "enable"
                when: !_TELKB.visible && !_GMDIALOG.visible
                PropertyChanges { target: root; enabled: true }
            },
            State {
                name: "disable"
                when: _TELKB.visible || _GMDIALOG.visible
                PropertyChanges { target: root; enabled: false }
            }
        ]
    }
}
