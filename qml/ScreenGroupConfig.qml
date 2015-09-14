import QtQuick 1.1
Rectangle {
	id: screenGroupConfig
	width: 100; height: 100
	property int itemWidth: 100
	property variant sWindow
	property alias columns: grid.columns
	property alias rows: grid.rows
	property alias spacing: grid.spacing
	color: "blue"
	Connections {
		target: grpManager
	}
	Grid {
		id: grid
		anchors {
			top: parent.top
			horizontalCenter: parent.horizontalCenter
			topMargin: 20
		}
		//default 4 columns
		spacing: 10
		Repeater {
			id: radioList
			model: modelRadio	
			RectTriState {
				property string name: modelData.getName()
				property bool isSelected: false
				height: itemWidth; width: itemWidth
				onSLongClicked: {
					isSelected = isSelected ? false : true;
					console.log("----" + name + "----" + isSelected);
				}
				onSClicked: {
					isSelected = isSelected ? false : true;
					console.log("----" + name + "----" + isSelected);
					if (_iState == 0) {
						iState = 1;
					} else if (_iState == 1) {
						iState = 0
					} else if (_iState == 2) {
						iState = 0
					}
				}
				Text {
					text: modelData.getRadioInfo();
				}
			}
		}
	}
	Rectangle {
		id: groupName
		width: itemWidth * 2; height: itemWidth/2
		anchors.top: grid.bottom
		anchors.right: grid.right
		border.width: 1
		TextInput {
			id: textbox
			text: "group name"
			font.family: "ubuntu"
			font.pixelSize: 18
			anchors.verticalCenter: parent.verticalCenter
			focus: true
			cursorVisible: true
			maximumLength: 10
			MouseArea {
				anchors.fill: parent
				onClicked: {
					if (textbox.text == "group name") {
						textbox.text = "";
					}
				}
			}
		}
	}
	RectCommonButton {
		id: configGroupButton
		anchors.top: groupName.bottom
		anchors.right: groupName.right
		width: itemWidth; height: itemWidth
		anchors.topMargin: 30
		description: "Create"	
		textSize: 14
		textAnchors {
			centerIn: configGroupButton
		}
		MouseArea {
			anchors.fill: parent
			onClicked: {
				configGroupButton.pressed = true;
				configGroupButton.pressed = false;
				var group="";
				for (var i=0;i<radioList.count;i++) {
					if (radioList.itemAt(i).isSelected) {
						group += radioList.itemAt(i).name + ", " ; //create new group with numbers of radio name
					}
				}
				console.log("*****" + group + "*****");
				grpManager.addGroup(group, textbox.text);
			}
		}
	}
}
