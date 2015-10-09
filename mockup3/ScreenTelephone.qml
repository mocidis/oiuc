import QtQuick 1.1
ScreenCommon {
    color: "white"
	Connections {
		target: pstn
		onCallingState: {
			numberLCD.text = msg
		}
	}
	NumberLCD {
		id: numberLCD
		height: 60
		fontSize: 36
		anchors {
			top: parent.top
			left: parent.left
            right: parent.right
			leftMargin: 10
            rightMargin: 10
			topMargin: 30
		}
	}
    Rectangle {
		anchors {
			top: numberLCD.bottom
			left: parent.left
            right: parent.right
            bottom: parent.bottom
			leftMargin: 10
			topMargin: 30
            rightMargin: 10
		}
        border { width: 1; color: "red" }
	GridKeyBoard {
		id: numPad
		backgroundColor: "#003000"
		itemSize: 60
		spacing: 20
		columns: 3
		rows: 4
		onClicked: {
			numberLCD.changeText(label);
		}
	}
    }
	FunctionPad {
		id: funcPad
		anchors {
			top: numPad.top
			right: parent.right
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
