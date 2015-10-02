import QtQuick 1.1
ScreenCommon {
    color: "white"
	Connections {
		target: pstn
		onCallingState: {
			numberLCD.text = msg
		}
	}
	width: 100; height: 100
	NumberLCD {
		id: numberLCD
		lcdWidth: 300
		lcdHeight: 60
		fontSize: 36
		anchors {
			top: parent.top
			left: parent.left
			leftMargin: 10
			topMargin: 30
		}
	}
	GridKeyBoard {
		anchors {
			//horizontalCenter:parent.horizontalCenter
			top: numberLCD.bottom
			left: parent.left
			leftMargin: 10
			topMargin: 30
		}
		id: numPad
		backgroundColor: "#003000"
		itemSize: 80
		spacing: 20
		columns: 3
		rows: 4
		onClicked: {
			numberLCD.changeText(label);
			numberLCD.fontSize = numberLCD.fontSize;
		}
	}
    //BorderImage {
		//anchors {
			//top: numPad.top
			//left: numberLCD.right
			//leftMargin: 20
			//topMargin: 50
		//}
        //source: "../static/seperator-black.svg"
        ////border { left: 1; right: 1; top: 1; bottom: 1 }
		//height: 200
		//width: 2
		//clip: true
	//}
	FunctionPad {
		id: funcPad
		anchors {
			//top: numPad.top
			//left: numPad.right
			top: numPad.top
			left: numberLCD.right
			leftMargin: 40
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
