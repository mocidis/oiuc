import QtQuick 2.0

Rectangle {
    id: root
    width: 800
    height: 600
    Rectangle {
        id: inputContainer
        width: 200
        height: 30
        border {
            width: 1
            color: "lightgray"
        }
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        TextInput {
            id: input
            anchors {
                fill: parent
            }
            text: "7653834"
            MouseArea {
                anchors {
                    fill: parent
                }
                onClicked: {
                    _KEYBOARD.textInput = input
                    input.cursorVisible = true
                }
            }
        }
    }

    VirtualKeyboard {
        id: _KEYBOARD
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }
    StateGroup {
        states: [
            State {
                name: "keyboardShown"
                when: _KEYBOARD.visible == true
                PropertyChanges { target: inputContainer.anchors; bottom: _KEYBOARD.top }
            },
            State {
                name: "keyboardHiden"
                when: _KEYBOARD.visible == false
                PropertyChanges { target: inputContainer.anchors; bottom: root.bottom }
            }
        ]
    }
}
