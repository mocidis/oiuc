import QtQuick 1.1

Rectangle {
	property alias text: call_number.text
	property int lcdWidth: 250
	property int lcdHeight: 40
	property int fontSize: 22
	width: lcdWidth; height: lcdHeight
	FontLoader {id: lcdFont; source: "../static/fonts/digital-7.ttf"}
	Image {
		source: "../static/LCD-Box-black.svg"
		TextInput {
			id: call_number
			width: lcdWidth; height: lcdHeight
			text: "enter number"
			readOnly: true
			font.family: lcdFont.name
			font.pixelSize: fontSize
			font.letterSpacing: 3
			anchors {
				fill: parent
				top: parent.top
				left: parent.left
				right: parent.right
				topMargin: 10
				leftMargin: 10
				rightMargin: 5
			}
		}
	}
	function changeText (value) {
		value = String(value);
		if (value === "CLR") {
			call_number.text = "enter number"
			return;
		}
		if (call_number.text == "enter number") {
			call_number.text = value;
		} else {
			call_number.text += value;
		}
	}
}
