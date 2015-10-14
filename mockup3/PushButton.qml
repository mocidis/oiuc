import QtQuick 1.1

Rectangle {
    signal pressed()
    signal clicked()
    signal longClicked()
	signal released();
    
    id: root

    MouseArea {
        id: mouseArea
        width: parent.width
        height: parent.height
        onPressed: {
            parent.pressed();
        }
        onClicked: {
            parent.clicked();
        }
        onPressAndHold: {
            parent.longClicked();
        }
		onReleased: {
			parent.released();
		}
    }
    state: "NORMAL"

    states: [
        State {
            name: "NORMAL"
            when: mouseArea.pressed == false
        },
        State {
            name: "PRESSED"
            when: mouseArea.pressed == true
            PropertyChanges {target: root; color: "lightgray"}
        }
    ]

/*    transitions: [
        Transition {
            from: "PRESSED"
            to: "NORMAL"
            ColorAnimation {duration: 200}
        }
    ] */
}
