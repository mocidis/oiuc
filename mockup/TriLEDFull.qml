import QtQuick 2.0

TriLEDCommon {
    property alias redLabel: redtxt.text
    property alias yellowLabel: yellowtxt.text
    property alias greenLabel: greentxt.text
    property bool columnFormat: true

    red: redRect
    green: greenRect
    yellow: yellowRect

    spacing: 3
    flow: columnFormat ? Flow.TopToBottom : Flow.LeftToRight
    Flow {
        width: columnFormat ? parent.width : parent.width/5
        flow: columnFormat ? Flow.LeftToRight : Flow.TopToBottom
        spacing: 8
        Circle {
            id: redRect
            width: 20
            color: dimColor
        }
        Text {
            id: redtxt
            color: "white"
            height: red.height
            verticalAlignment: Text.AlignVCenter
            text: "Error"
        }
    }
    Flow {
        width: columnFormat ? parent.width : parent.width/5
        flow: columnFormat ? Flow.LeftToRight : Flow.TopToBottom
        spacing: 8
        Circle {
            id: yellowRect
            width: 20
            color: dimColor
        }
        Text {
            id: yellowtxt
            color: "white"
            height: yellow.height
            verticalAlignment: Text.AlignVCenter
            text: "PTT"
        }
    }
    Flow {
        width: columnFormat ? parent.width : parent.width/5
        flow: columnFormat ? Flow.LeftToRight : Flow.TopToBottom
        spacing: 8
        Circle {
            id: greenRect
            width: 20
            color: dimColor
        }
        Text {
            id: greentxt
            color: "white"
            height: green.height
            verticalAlignment: Text.AlignVCenter
            text: "Squelch"
        }
    }
}
