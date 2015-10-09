import QtQuick 1.1

Rectangle {
    property int iState: 0;
    property alias text: intext.text
    property variant panel: null
    property int tabIndex: -1
    property int modelIndex: -1
    property alias oModelItem: indicator.oModelItem
    
    signal clicked(int modelIndex, int tabIndex, int iState)

    id: root
    
    width: 80
    height: width
    radius: 10

    function toggleActive() {
        if(iState < 2) iState = ( iState + 1 ) % 2;
        else return;
    }
    function toggleControlled() {
        if (iState == 1) iState = 2;
        else if (iState == 2) iState = 1;
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
            anchors {
                horizontalCenter:parent.horizontalCenter
                bottom: parent.bottom
            }
            itemWidth: 5
        }
    }
	StateGroup {
		state: "inactive"

		states: [
			State {
				name: "inactive"
				when: iState == 0
				PropertyChanges {target: root; color: "lightgray"}
                PropertyChanges {target: inner; color: "white"; border.color: "lightgray" }
                PropertyChanges {target: intext; color: "lightgray" }
			}, 
			State {
				name: "active"
				when: iState == 1
				PropertyChanges {target: root; color: "lightgray"}
                PropertyChanges {target: inner; color: "white"; border.color: "black"}
                PropertyChanges {target: intext; color: "black" }
			},
			State {
				name: "controlled"
				when: iState == 2
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
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (iState < 1) return;
            parent.toggleControlled();
            parent.clicked(modelIndex, tabIndex, iState);
            if (panel != null) {
                if (iState > 1)
                    panel.hShow(modelIndex, tabIndex);
                else {
                    panel.hShow(-1, 0);
                }
            }
            else {
                console.log("Please bind panel and tabIndex properties to correct values");
            }
        }
        onPressAndHold: iState = (iState < 2)?( iState + 1 ) % 2 : iState //parent.toggleActive();
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
    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            var v, v1, bv;
            v = Math.random();
            v1 = Math.random();
            bv = (v1 > 0.5);
            if( v < 0.33) {
                indicator.setRed(bv);
            }
            else if (v < 0.67) {
                indicator.setYellow(bv);
            }
            else {
                indicator.setGreen(bv);
            }
        }
    }
}
