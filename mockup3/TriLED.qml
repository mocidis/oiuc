import QtQuick 1.1
TriLEDCommon {
    property int itemWidth: 6
	property int fullLed: 0 //0 - fullLED radio, 1 - OIUC, 2 - GROUP
    spacing: 2
    red: redRect
    green: greenRect
    yellow: yellowRect
	Component.onCompleted: {
		if (fullLed == 1) {
			yellowRect.visible = false;
			greenRect.visible = false;
		} else if (fullLed == 2) {
			redRect.visible = false;	
			yellowRect.visible = false;
			greenRect.visible = false;
		}
	}
    Rectangle {
        id: redRect
        width: itemWidth
        height: width
        color: dimColor
    }
    Rectangle {
        id: yellowRect
        width: itemWidth
        height: width
        color: dimColor
    }
    Rectangle {
        id: greenRect
        width: itemWidth
        height: width
        color: dimColor
    }
}
