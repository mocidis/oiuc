import QtQuick 1.1
Rectangle {
	width: 150; height: 100
	Timer {
		interval: 500; running: true; repeat: true
		onTriggered: time.text = Qt.formatDateTime(new Date(), "hh:mm:ss\ndd/MM/yyyy")
	}
	Text {
		id: time
		anchors.centerIn: parent
		text: "--/--/--"
		font.family: "ubuntu"
		font.pixelSize: 16
	}
}
