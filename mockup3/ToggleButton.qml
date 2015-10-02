import QtQuick 1.1

Rectangle {
    signal clicked()
    signal longClicked()
    id: root
    property bool value: false
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            parent.value = !parent.value;
            parent.clicked();
        }
        onPressAndHold: {
            parent.longClicked();
        }
    }
    StateGroup {
        state: "OFF"

        states: [
            State {
                name: "OFF"
                when: value == false
            },
            State {
                name: "ON"
                when: value == true
                PropertyChanges {target: root; color: "lightgray"}
            }
        ]

        transitions: [
            Transition {
                from: "ON"
                to: "OFF"
                ColorAnimation {duration: 200}
            },
            Transition {
                from: "OFF"
                to: "ON"
                ColorAnimation {duration: 200}
            }
        ]
    }
}
