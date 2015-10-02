import QtQuick 2.0
PushButton {
    property alias text: label.text
    property alias textColor: label.color
    property string value: null
    property alias textSize: label.font.pointSize
    property bool isCap: false
    height: width
    id: root
    Text {
        id: label
        anchors.centerIn: parent
        color: "gray"
        font {
            pointSize: 20
        }
    }
    border {
        width: 1
        color: "lightgray"
    }
    StateGroup {
        states: [
            State {
                name: "lowerCase"
                when: !root.isCap
                PropertyChanges { target: label; text: value.toLowerCase() }
            },
            State {
                name: "upperCase"
                when: root.isCap
                PropertyChanges { target: label; text: value.toUpperCase() }
            }
        ]
    }
}

