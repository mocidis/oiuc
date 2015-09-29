import QtQuick 2.0

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
            id: iconImg
            anchors.fill: parent
            source: "../static/Speaker-fill-black-small.svg"
            sourceSize {
                width: parent.width * 0.7
                height: width
            }
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
            color: "black"
            font {
                pointSize: 24
            }
        }
        onClicked: {
            if( iValue > 0 ) iValue--;
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
            color: "black"
            font {
                pointSize: 24
            }
        }
        onClicked: {
            if( iValue < 100 ) iValue++;
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
        Text {
            anchors.centerIn: parent
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
