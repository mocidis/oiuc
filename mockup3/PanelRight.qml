import QtQuick 1.1
PanelCommon {
	id: root
	Connections {
		target: logObj
		onWriteLog: {
		    logModel.insert(
                0, 
                {
                    "log": Qt.formatDateTime(new Date(), "[hh:mm] ") + msg
                }
            ); 
		}
	}
	ListModel {
		id: logModel
        ListElement {
            log: "test messages"
            count: 0
        }
        ListElement {
            log: "Test messages Test messages Test messages Test messages Test messages Test messages "
            count: 1
        }
        ListElement {
            log: "TEst messages"
            count: 2
        }
	}
	ListView {
		id: listview
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
			bottom: parent.bottom
		}
		model: logModel
		delegate: Rectangle {
            width: parent.width
            height: 30
            color: (index % 2 == 0) ? "white":"#F0F0F0"
			Text {
                anchors {
                    left: parent.left
                    leftMargin: 5
                    verticalCenter: parent.verticalCenter
                }
				width: root.width
				text: log
				elide: Text.ElideRight
			}
		}
		clip: true
	}
	ScrollBar {
		scrollArea: listview; width: 8
		anchors { right: listview.right; rightMargin: 8; bottom: listview.bottom ; top: listview.top}
	}
}

