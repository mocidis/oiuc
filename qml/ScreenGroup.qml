import QtQuick 1.1

Rectangle {
	id: thanhnt
	width: 100; height: 100
	property alias text: desc.text
	property alias radioListText: radioListText.text
	property variant screenGroup
	property int sIndex
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
	Rectangle {
		id: deleteGroup
		width: 100; height: 100
		color: "white"
		anchors {
			bottom: parent.bottom
			right: parent.right
		}
		Text {
			text: "Destroy"
		}
		MouseArea {
			anchors.fill: parent
			onClicked: {
				screenGroup.itemAt(sIndex).destroy();
				grpManager.deleteGroup(modelGroup[sIndex].getName());
			}
		}
	}
}
