import QtQuick 1.1

Flow {
    property string normalSource: ""
    property string muteSource: ""
    property int iValue: 50
    spacing: 4
    PushButton {
        height: parent.height
        width: parent.height
        radius: 3
        color: "transparent"
        Image {
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            id: iconImg
            anchors.centerIn: parent
            source: "../static/Speaker-fill-black-small.svg"
            smooth: true
        }
        onClicked: {
            iValue = 0;
            iconImg.source = muteSource;
        }
    }
    Rectangle {
        color: "lightgray"
        width: 1
        height:parent.height
    }
    PushButton {
        width: parent.height
        height: parent.height
        radius: 3
        color: "transparent"
        Text {
            anchors.centerIn: parent
            text: "-"
            color: "white"
            font {
                pixelSize: 24
            }
        }
        onClicked: {
            if( iValue > 0 ) iValue -= 10;
            else iValue = 0
        }
    }
    Rectangle {
        color: "lightgray"
        width: 1
        height:parent.height
    }
    PushButton {
        width: parent.height
        height: parent.height
        radius: 3
        color: "transparent"
        Text {
            anchors.centerIn: parent
            text: "+"
            color: "white"
            font {
                pixelSize: 24
            }
        }
        onClicked: {
            if( iValue < 100 ) iValue += 10;
            else iValue = 100
        }
    }
    Rectangle {
        color: "lightgray"
        width: 1
        height:parent.height
    }
    Rectangle {
        width: parent.height
        height: parent.height
        color: "transparent"
        Text {
            anchors.centerIn: parent
            color: "white"
            text: "" + iValue
        }
    }
    StateGroup {
        states: [
            State {
                name: "normal"
                when: iValue > 0
                PropertyChanges { target: iconImg; source: normalSource }
            },
            State {
                name: "mute"
                when: iValue <= 0
                PropertyChanges { target: iconImg; source: muteSource }
            }
        ]
    }
}
