import QtQuick 1.1

Rectangle {
	width: 100; height: 100
	property alias text: desc.text
	property alias radioListText: radioListText.text
	color: "blue"
	Text {
		id: desc
		text: "text input"
	}
	Rectangle {
		id: radioList
		anchors {
			top: desc.bottom
		}
		Text {
			id: radioListText
		}
	}
}
