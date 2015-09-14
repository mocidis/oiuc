import QtQuick 1.1
Rectangle {
	property int iState: 0 // inactive: 0; active: 1; controlled: 2
	
	property bool isDoubleClicked: false

	id: endpoint
	width: 150; height: 50

    signal sClicked(int _iState)
    signal sLongClicked(int _iState)

	function onControlled(bOn) {
		if(bOn) {
			if(iState == 1) iState = 2;
		}
		else {
			if(iState == 2) iState = 1;
		}
	}
	border {
		width:1
		color:"black"
	}
	MouseArea {
		anchors.fill: parent
		onPressAndHold: {
			if( parent.iState == 0 ) parent.iState = 1;
			else if (parent.iState == 1) parent.iState = 0;
			sLongClicked(iState);
		}
		onClicked: {
			if( parent.iState == 1 ) parent.iState = 2;
			else if (parent.iState == 2) parent.iState = 1;
			sClicked(iState);
		}
	}


	StateGroup {
		state: "inactive"

		states: [
			State {
				name: "inactive"
				when: iState == 0
				PropertyChanges {target: endpoint; color: "grey"}
			}, 
			State {
				name: "active"
				when: iState == 1
				PropertyChanges {target: endpoint; color: "lightgray"}
			},
			State {
				name: "controlled"
				when: iState == 2
				PropertyChanges {target: endpoint; color: "#33cc33"}
			}
		]

		transitions: [
			Transition {
				from: "*"; to: "*"
				ColorAnimation {target: endpoint; properties: "color"; duration: 300}
			}
		]
	}
}
