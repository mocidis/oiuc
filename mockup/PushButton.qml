import QtQuick 1.1

Rectangle {
    signal clicked()
    signal longClicked()
    
    id: root

    MouseArea {
        id: mouseArea
        width: parent.width
        height: parent.height
        onClicked: {
            parent.clicked();
        }
        onPressAndHold: {
            parent.longClicked();
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

    transitions: [
        Transition {
            from: "PRESSED"
            to: "NORMAL"
            ColorAnimation {duration: 200}
        }
    ]
}
