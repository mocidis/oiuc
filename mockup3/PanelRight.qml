import QtQuick 1.1
PanelCommon {
	id: root
	Connections {
		target: logObj
		onWriteLog: {
			log(msg);
		}
	}
	function log(line) {
		line = Qt.formatDateTime(new Date(), "  [hh:mm] ") + line
		logModel.insert(0, {"log": line}); 
	}
	ListModel {
		id: logModel
	}
	Component {
		id: logComponent
		Column {
			spacing: 2
			Text {
				width: root.width
				text: log
				elide: Text.ElideRight
			}
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
		delegate: logComponent
		clip: true
	}
	ScrollBar {
		scrollArea: listview; width: 8
		anchors { right: listview.right; rightMargin: 8; bottom: listview.bottom ; top: listview.top}
	}
}

