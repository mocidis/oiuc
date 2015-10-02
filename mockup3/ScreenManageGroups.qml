import QtQuick 1.1
ScreenCommon {
    color: "white"
	width: 100; height: 100
	Flickable {
		id: radioList
		width: parent.width - 10
		height: parent.height - 80
		contentHeight: {
			console.log( "______+++++: " +  (80 + (80 * Math.ceil(_ROOT.models[0].count/5))));
			return (100 * Math.ceil(_ROOT.models[0].count/5));
		}
		anchors {
			left: parent.left
			top: parent.top
			leftMargin: 10
		}
		clip: true
		Flow {
			width: parent.width
			flow: Flow.LeftToRight
			spacing: 20
			Repeater {
				id: radioRepeater
				model: _ROOT.models[0]
				ButtonRadio { 
					property string namet: _ROOT.models[0].get(index).name
					text: name 
					//oModelItem: radioRepeater.model.get(index)
					MouseArea {
						anchors.fill: parent
						onClicked: {
							if (iState == 0) {
								iState = 2;
							} else {
								iState = 0;
							}
						}
					}
				}
			}
		}
	}
	ScrollBar {
		scrollArea: radioList; width: 8
		anchors { right: radioList.right; bottom: radioList.bottom ; top: radioList.top}
	}
	Rectangle {
		width: parent.width
		height: 80
		anchors {
			left: parent.left
			bottom: parent.bottom
			leftMargin: 10
		}
		color: "white"
		Row {
			spacing: 50
			anchors {
				centerIn: parent
			}
			CirclePushButton {
				borderBrightColor: "white"
				borderDarkColor: "gray"
				backgroundColor: "#002000"
				textFontSize: 16
				borderWidth: 2
				textColor: "white"
				width: 120
				height: 80
				text: "CLEAR"
				onClicked: {
					for (var i=0;i<radioRepeater.count;i++) {
						radioRepeater.itemAt(i).iState = 0;
					}
				}
			}
			Rectangle {
				width: 120
				height: 70
				border.width: 2
				TextInput {
					id: grpName
					text: "2525"
				}
			}
			CirclePushButton {
				borderBrightColor: "white"
				borderDarkColor: "gray"
				backgroundColor: "#002000"
				textFontSize: 16
				borderWidth: 2
				textColor: "white"
				width: 120
				height: 80
				text: "CREATE"
				onClicked: {
					var group="";
					for (var i=0;i<radioRepeater.count;i++) {
						if (radioRepeater.itemAt(i).iState == 2) {
							group += radioRepeater.itemAt(i).namet +", " ; //create new group with numbers of radio name
						}
					}
					console.log("---------" + group);
					groupObj.addGroup(group, grpName.text);
				}
			}
		}
	}
}
