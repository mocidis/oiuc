import QtQuick 1.1

RectTriState {
	property int iIndex: -1
	property variant eContainer
	property variant eTabs
	property alias text: desc.text
	width: endpointPanel.itemWidth
	height: width
	onSLongClicked: {
		console.log("RectRadio Long clicked " + iIndex  + _iState);
	}
	onSClicked: {
		console.log("RectRadio Single clicked " + iIndex + _iState);
	}
	Text {
		id: desc
		text: "Radio " + (iIndex+1);
	}
}
