import QtQuick 1.0

Rectangle {
    id: slider; width: 244; height: 30
    property int value: 1
    property int xMax: width - handle.width - 4
	signal updateSpeakerVolume(int volume)

	border.color: "black"; border.width: 3; radius: 8
	Rectangle {
        id: handle; smooth: true
		color: "black"
        width: 40; height: slider.height-10; radius: 10
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.topMargin: 5
		anchors.bottomMargin: 5
        MouseArea {
            id: mouse
            anchors.fill: parent; drag.target: parent
			drag.axis: Drag.XAxis; drag.minimumX: 0; drag.maximumX: slider.xMax
			onPositionChanged: { 
				value = Math.floor(handle.x/2);
				console.log("Speaker volume: " + value);
				updateSpeakerVolume(value)
			}
        }
    }
}
