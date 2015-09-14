import QtQuick 1.1

Rectangle {
	id: root
	width: 150 ; height: 100
	property int iIndex: -1;
	property variant eContainer;
	property variant eTabs;
	property alias source: image.source
	property alias description: desc.text
	property alias textAnchors: desc.anchors
	property alias textSize: desc.font.pixelSize
	property bool pressed: false
	//color: "grey"
	Image {
		anchors.centerIn: parent
		id: image
		smooth: true
		clip: true
		fillMode: Image.PreserveAspectFit
	}
	Text {
		id: desc
		anchors.bottom: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		text: "..."
		smooth: true
	}
	MouseArea {
		anchors.fill: parent
		onClicked: {
			root.pressed = true
			root.pressed = false
			eTabs.showVTab(iIndex, "true");
			console.log("clicked");
		}
	}
    state: "NORMAL"
    states: [
        State {
            name: "NORMAL"
            when: root.pressed == false
            PropertyChanges {
                target:root
                color: "yellow"
            }
        },
        State {
            name: "PRESSED"
            when: root.pressed == true
            PropertyChanges {
                target:root
                color: "lightgray"
            }
        }
    ]
    transitions: Transition {
        from: "PRESSED"
        to: "NORMAL"
        ColorAnimation { duration: 200 }
    }
}
