import QtQuick 2.0

TriLEDCommon {
    property alias redLabel: redtxt.text
    property alias yellowLabel: yellowtxt.text
    property alias greenLabel: greentxt.text

    red: redRect
    green: greenRect
    yellow: yellowRect

    spacing: 3
    flow: Flow.TopToBottom
    Flow {
        width: parent.width
        spacing: 8
        Circle {
            id: redRect
            width: 20
            color: dimColor
        }
        Text {
            id: redtxt
            height: red.height
            verticalAlignment: Text.AlignVCenter
            text: "Error"
        }
    }
    Flow {
        width: parent.width
        spacing: 8
        Circle {
            id: yellowRect
            width: 20
            color: dimColor
        }
        Text {
            id: yellowtxt
            height: yellow.height
            verticalAlignment: Text.AlignVCenter
            text: "PTT"
        }
    }
    Flow {
        width: parent.width
        spacing: 8
        Circle {
            id: greenRect
            width: 20
            color: dimColor
        }
        Text {
            id: greentxt
            height: green.height
            verticalAlignment: Text.AlignVCenter
            text: "Squelch"
        }
    }
}
