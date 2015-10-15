import QtQuick 1.1

TriLEDCommon {
    property alias redLabel: redtxt.text
    property alias yellowLabel: yellowtxt.text
    property alias greenLabel: greentxt.text
    property bool columnFormat: true
	property int fullLed: 0 //0 - fullLed radio, 1 - oiuc, 2 - group
    red: redRect
    green: greenRect
    yellow: yellowRect

    spacing: 3
    flow: columnFormat ? Flow.TopToBottom : Flow.LeftToRight
	Component.onCompleted: {
		if (fullLed == 1) {
			pttLed.visible= false;
			sqLed.visible = false;
		} else if (fullLed == 2) {
			errLed.visible = false;
			pttLed.visible= false;
			sqLed.visible = false;
		}
	}
    Flow {
		id: errLed
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
		id: pttLed
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
		id: sqLed
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
