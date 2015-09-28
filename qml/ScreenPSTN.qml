import QtQuick 1.1
Rectangle {
	Connections {
		target: pstn
		onCallingState: {
			numberLCD.text = msg
		}
	}
	width: 100; height: 100
	NumberLCD {
		id: numberLCD
		lcdWidth: numPad.width
		lcdHeight: 50
		fontSize: 30
		anchors {
			top: parent.top
			horizontalCenter: parent.horizontalCenter
			topMargin: 30
		}
	}
	GridKeyBoard {
		anchors {
			horizontalCenter:parent.horizontalCenter
			top: numberLCD.bottom
			topMargin: 30
		}
		id: numPad
		backgroundColor: "#003000"
		itemSize: 80
		spacing: 30
		columns: 3
		rows: 4
		onClicked: {
			numberLCD.changeText(label);
			numberLCD.fontSize = numberLCD.fontSize;
		}
	}
	FunctionPad {
		id: funcPad
		anchors {
			top: numPad.top
			left: numPad.right
			leftMargin: 20
		}
		onClicked: {
			detectPSTNButton(value)
		}
	}

	function detectPSTNButton (value) {
		switch (value) {
			case "Call":
				console.log(numberLCD.text);
				pstn.pstnCall(numberLCD.text);
				break;
			case "Ha":
				console.log(value);
				pstn.pstnHangupCall(numberLCD.text);
				break;
			case "Ha all":
				console.log(value);
				pstn.pstnHangupAllCall(numberLCD.text);
				break;
			case "Trans":
				console.log(value);
				pstn.pstnTransferCall(numberLCD.text);
				break;
			case "Conf":
				console.log(value);
				pstn.pstnConferenceCall(numberLCD.text);
				break;
			case "Answer":
				console.log(value);
				pstn.pstnAnswerCall(numberLCD.text);
				break;
		}

	}
}
