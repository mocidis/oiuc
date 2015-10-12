import QtQuick 1.1

DialogCommon {
    id: root
    captionText: "Create groups"
    onClose: visible = false
    Flow {
        spacing: 5
        flow: Flow.TopToBottom
        anchors { 
            left: parent.left
            right: parent.right
            top: caption.parent.bottom
            bottom: parent.bottom
            margins: 20 
        }
        Item {
            width: parent.width
            height: 30
            PushButton {
                border { width: 2; color: "gray" }
                anchors {
                    left: parent.left
                    right: parent.horizontalCenter
                    rightMargin: 5
                    top: parent.top
                    bottom: parent.bottom
                }
                Text {
                    anchors { centerIn: parent }
                    text: "Create"
                }
                onClicked: {
					var group="";
					for (var i=0;i<repeater.count;i++) {
						if (repeater.itemAt(i).value == true) {
							group += repeater.itemAt(i).namet +", " ; //create new group with numbers of radio name
						}
					}
					console.log("---------" + group);
					groupObj.addGroup(group, groupName.text, descText.text);
                }
            }
            PushButton {
                border { width: 2; color: "gray" }
                anchors {
                    left: parent.horizontalCenter
                    leftMargin: 5
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                Text {
                    anchors { centerIn: parent }
                    text: "Reset"
                }
                onClicked: {
                    for ( var i = 0; i < repeater.count; i++ ) {
                        repeater.itemAt(i).value =  false;
                    }
                }
            }
        }
        Rectangle {
            border { width: 1; color: "gray" }
            width: parent.width
            height: 30
            TextInput {
                id: groupName
                anchors {
                    verticalCenter : parent.verticalCenter
                    left: parent.left
                    right: parent.right
                    leftMargin: 10
                }
                text: "Group 1"
                maximumLength: 7
                font {
                    italic: true
                }
            }
            MouseArea {
                anchors { fill: parent }
                onClicked: {
                    if ( _KEYBOARD.textInput != null )
                        _KEYBOARD.textInput.cursorVisible = false;
                    _KEYBOARD.textInput = groupName;
                    _KEYBOARD.textInput.cursorVisible = true;
                }
            }
        }
        Rectangle {
            border { width: 1; color: "gray" }
            width: parent.width
            height: 30
            TextInput {
                id: descText
                anchors {
                    verticalCenter : parent.verticalCenter
                    left: parent.left
                    right: parent.right
                    leftMargin: 10
                }
                text: "Description"
                font {
                    italic: true
                }
            }
            MouseArea {
                anchors { fill: parent }
                onClicked: {
                    if ( _KEYBOARD.textInput != null )
                        _KEYBOARD.textInput.cursorVisible = false;
                    _KEYBOARD.textInput = descText;
                    _KEYBOARD.textInput.cursorVisible = true;
                }
            }
        }
        Rectangle {
            width: parent.width
            height: parent.height - 110
            border { width: 1; color: "gray" }
            clip: true
            Flickable {
                id: scrollArea
                anchors {
                    fill: parent
                }
                contentHeight: parent.height - 1
				Flow {
					id: flow1

                    flow: Flow.TopToBottom
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                        margins: 1
                    }
                    spacing: 1
                    Repeater {
                        id: repeater
                        model: _ROOT.models[0]
						ToggleButton {
							property string namet: _ROOT.models[0].get(index).name
                            width: flow1.width
                            height: 40
                            color: (index % 2 == 0) ? "white":"#F0F0F0"
                            Text {
                                anchors { 
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                    right: parent.right
                                    leftMargin: 10
                                }
                                text: namet  + "\n" + description
                                color: value ? "white" : "black"
                            }
                            onColor: "darkgray"
                        }
                    }
                }
            }
            ScrollBar {
                scrollArea: scrollArea
                anchors { 
                    right: scrollArea.right; 
                    bottom: scrollArea.bottom ; 
                    top: scrollArea.top
                }
            }
        }
    }
}
