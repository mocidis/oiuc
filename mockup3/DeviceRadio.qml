import QtQuick 1.1

//Flow {
Item {
	Connections {
		target: ptt
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
    function getFreq() {
        if (oModelItem == null) return -1;
        return oModelItem.frequency;
    }

    //flow: Flow.TopToBottom
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
                anchors {
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }
                width: parent.width / 5
            }
            Rectangle {
                width: parent.width/2
                //color: "#F0F0F0"
                color: "#A0B46A"
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    horizontalCenter: parent.horizontalCenter
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
                            text: getFreq() + " MHz"
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
            PushButton {
                id:ptt_button
                width: parent.width / 5
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                }
                radius: 10
                color: "#662222"
                Text {
                    anchors {
                        centerIn:parent
                    }
                    text: "PTT"
                    font {
                        pixelSize: 18
                        bold: true;
                    }
                    color: "white"
                }
				onPressed: {
					ptt.setPTT(index, 0, 1);
				}
				onReleased: {
					ptt.setPTT(index, 0, 0);
				}
				
            }
        }
        Rectangle {
            height: 50
            width: 200
            radius: 8
            color: "darkgray"
            anchors {
                left: parent.left
                bottom: parent.bottom
                leftMargin: 20
                bottomMargin: 10
            }
            Spinner {
                height: 40
                width: 190
                anchors.centerIn: parent
                normalSource: "../static/Speaker-fill-white-small.svg"
                muteSource: "../static/Speaker-mute-fill-white-small.svg"
            }
        }
        Rectangle {
            height: 50
            width: 200
            radius: 8
            color: "darkgray"
            anchors {
                right: parent.right
                bottom: parent.bottom
                rightMargin: 20
                bottomMargin: 10
            }
            Spinner {
                height: 40
                width: 190
                anchors.centerIn: parent
                normalSource: "../static/Mic-fill-white-small.svg"
                muteSource: "../static/Mic-mute-fill-white-small.svg"
            }
        }
    }
/*
    Item {
        width: parent.width
        height: 5
        Rectangle {
            width: 40
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                leftMargin: 50
            }
            color: "grey"
        }
        Rectangle {
            width: 40
            anchors {
                top: parent.top
                bottom: parent.bottom
                right: parent.right
                rightMargin: 50
            }
            color: "grey"
        }
    }
*/
}
