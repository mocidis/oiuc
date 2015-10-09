import QtQuick 1.1

Rectangle {
	property alias text: call_number.text
    property alias textInput: call_number
	property int fontSize: 32
	//FontLoader {id: lcdFont; source: "../static/fonts/digital-7 (mono).ttf"}
    //color: "darkgray"
    color: "#A0B46A"
    border { width: 1; color: "black" }
	TextInput {
		width: parent.width
		text: "88888888888888888"
        color: "#9DA267"
		readOnly: true
		font {
            family: lcdFont.name
		    //pixelSize: fontSize
		    pointSize: fontSize
		    letterSpacing: 3
        }
		anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            margins: 10
		}
	}
	TextInput {
		id: call_number
		width: parent.width
        maximumLength: 17
		text: ""
        color: "black"
		readOnly: true
		font {
            family: lcdFont.name
		    //pixelSize: fontSize
		    pointSize: fontSize
		    letterSpacing: 3
        }
		anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            margins: 10
		}
	}
	function changeText (value) {
		value = String(value);
		if (value === "CLR") {
			call_number.text = "enter number"
			return;
		}
		if (call_number.text == "enter number") {
			call_number.text = value;
		} else {
			call_number.text += value;
		}
	}
}
