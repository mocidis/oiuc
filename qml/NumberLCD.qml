import QtQuick 1.1

Rectangle {
	property alias text: call_number.text
	property int my_width: 250
	property int my_height: 40
	property int font_size: 22
	width: my_width; height: my_height
	border.width: 2
	TextInput {
		id: call_number
		width: my_width; height: my_height
		text: "enter number"
		readOnly: true
		font.family: "ubuntu"
		font.pixelSize: font_size
		font.letterSpacing: 1.2
		anchors.margins: 20
		anchors.verticalCenter: parent.verticalCenter
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
