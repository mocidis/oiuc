import QtQuick 1.1

Rectangle {
	width: 100
	height: 100
	function writeLog(line) {
		logContent.text += "\n" + line;
	}
	border.width: 1
	border.color: "black"
	Text {
		id: logContent
		text: "LogPanel"
	}
}
