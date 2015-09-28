import QtQuick 1.1

Rectangle {
	width: 100; height: 100
	property alias text: desc.text
	color: "blue"
	Text {
		id: desc
		text: "default"
	}
	Slider {
		id: slider
		anchors {
			top: desc.bottom 
		}
	}
}
