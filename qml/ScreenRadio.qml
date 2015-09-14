import QtQuick 1.1
Rectangle {
	property alias text: text_info.text
	Text {
		id: text_info
		font.family: "ubuntu"
		font.pixelSize: 16
		text: "default text"
	}
}
