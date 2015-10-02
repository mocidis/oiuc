import QtQuick 1.1

Rectangle {
	id: root
	color: "white"
    width: 800
	height: 600
	Flickable {
		id: aflickable
		contentHeight: 4000
		anchors {
			fill: parent
			margins: 50
		}
		Rectangle {
			anchors {
				top: parent.top
				left: parent.left
			}
			width: parent.width
			height: 400
			color: "yellow"
		}
	}
	ScrollBar {
		width: 8
		anchors {
			top: parent.top
			bottom: parent.bottom
			right: parent.right
		}
		scrollArea: aflickable
	}
}
