import QtQuick 1.1

Item {
	Connections {
		target: pstn
	}
    property alias oModelItem: indicator.oModelItem
    function getName() {
        if (oModelItem == null) return "NaN";
        return oModelItem.name;
    }
    function getDesc() {
        if (oModelItem == null) return "NaN";
        return oModelItem.description;
    }
    function getStatus() {
        if (oModelItem == null) return -1;
        return oModelItem.status;
    }
    anchors {
        fill: parent
    }
    Rectangle {
        width: parent.width
        height: 150
        color: "gray"
        //radius: 10
        Rectangle {
            height: parent.height * 0.45
            color: "transparent"
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                topMargin: 10
                leftMargin: 20
                rightMargin: 20
            }
            TriLEDFull {
                id: indicator
                dimColor: "lightgray"
				fullLed: 1
                anchors {
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }
                width: parent.width / 5
            }
            Rectangle {
				id: lcdDisplay
                width: parent.width - 100
                //color: "#F0F0F0"
                color: "#A0B46A"
                anchors {
                    top: parent.top
                    bottom: parent.bottom
					left: indicator.right
                    //horizontalCenter: parent.horizontalCenter
                }
                radius: 3
                border {
                    width: 1
                    color: "black"
                }
                Flow {
                    flow: Flow.TopToBottom
                    spacing: 5
                    anchors {
                        fill: parent
                        topMargin: 10
                        leftMargin: 15
                        rightMargin: 15
                    }
                    Item {
                        width: parent.width
                        height: nametext.height
                        Text {
                            id: nametext
                            anchors {
                                top: parent.top
                                left: parent.left
                            }
                            text: getName()
                        }
                        Text {
                            text: "S. " + getStatus()
                            anchors {
                                top: parent.top
                                right: parent.right
                            }
                        }
                    }
                    Text {
                        id: desctext
                        text: getDesc()
                        font {
                            pixelSize: 10
                            italic: true
                        }
                    }
                }
            }
        }
		PushButton {
			id:call_button
			width: parent.width
			height: parent.height - lcdDisplay.height - 20
			 anchors {
				 bottom: parent.bottom
				 left: parent.left
				 right: parent.right
				 leftMargin: 20
				 rightMargin: 20
				 bottomMargin: 5
			 }
			 radius: 10
			 color: "#0172b8"
			 Text {
				 anchors {
					 centerIn:parent
				 }
				 text: "CALL"
				 font {
					 pixelSize: 18
					 bold: true;
				 }
				 color: "white"
			 }
			 onPressed: {
				 pstn.pstnCall(name);
			 }
		 }
    }
}
