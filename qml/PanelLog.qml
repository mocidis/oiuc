import QtQuick 1.1

Rectangle {
	id: root
	width: 100
	height: 100
	Connections {
		target: logObj
		onWriteLog: {
			writeLog(msg);
		}
	}
	function writeLog(line) {
		line = Qt.formatDateTime(new Date(), "[hh:mm] ") + line
		logModel.insert(0, {"log": line}); 
	}
	border.width: 1
	border.color: "black"
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
		anchors.fill: parent
		model: logModel
		delegate: logComponent
	}
	MouseArea {
		anchors.fill: parent
		onClicked: {
			console.log(logObj.getFilename());
		}
	}
}
