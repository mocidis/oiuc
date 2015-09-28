import QtQuick 2.0
Flow {
    property int itemWidth: 6
    property bool isRed: false
    property bool isGreen: false
    property bool isYellow: false
    property color dimColor: "gray"
    spacing: 2
    Rectangle {
        id: red
        width: itemWidth
        height: width
        color: dimColor
    }
    Rectangle {
        id: yellow
        width: itemWidth
        height: width
        color: dimColor
    }
    Rectangle {
        id: green
        width: itemWidth
        height: width
        color: dimColor
    }
    StateGroup {
        states: [
            State {
                name: "RED"
                when: isRed
                PropertyChanges {target: red; color:"red"}
            }
        ]
    }
    StateGroup {
        states: [
            State {
                name: "GREEN"
                when: isGreen
                PropertyChanges {target: green; color:"lime"}
            }
        ]
    }
    StateGroup {
        states: [
            State {
                name: "YELLOW"
                when: isYellow
                PropertyChanges {target: yellow; color: "yellow"}
            }
        ]
    }
}
