import QtQuick 1.1
ScreenCommon {
    property variant oModelItem: null
    property alias contentHeight: flickable.contentHeight
    signal deleteClicked()
    visible: (oModelItem != null)?oModelItem.iState == 2:false
    Flickable {
        id: flickable
        anchors { fill: parent }
        Flow {
            id: flow1
            width: parent.width
            height: parent.height
            flow: Flow.TopToBottom
            Rectangle {
                width: parent.width
                height: 90
                color: "#E5E5E5"
                PushButton {
                    color: "#662222"
                    radius: 10
                    anchors {
                        fill: parent
                        topMargin: 15
                        bottomMargin: 15
                        leftMargin: 20
                        rightMargin: 20
                    }
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 24
                        font.bold: true
                        text: "Push-To-Talk"
                        color: "white"
                    }
                    onPressed : {
						ptt.setPTT(index, 2, 1);
                    }
					onReleased: {
						ptt.setPTT(index, 2, 0);
					}
                }
            }
            Repeater {
                id: groupRepeater
                model: (oModelItem != undefined) && (oModelItem != null) ? oModelItem.nodes : null
                DeviceRadioReduced {
                    width: flow1.width
                    height: 90
                    color: ( (index % 2) == 0 ) ? "#585858" : "#858585"
                    oModelItem: _ROOT.models[modelIdx].get(itemIdx)
                }
            }
        }
    }
    ScrollBar {
        scrollArea: flickable
        anchors { 
            right: flickable.right
            bottom: flickable.bottom
            top: flickable.top
        }
    }
    PushButton {
        anchors {
            right: parent.right
            bottom: parent.bottom
        }
        width: pbLabel.width + 60
        height: pbLabel.height + 30
        Text {
            id: pbLabel
            anchors { centerIn: parent }
            text : "DELETE"
            color: "darkgray"
        }
        onLongClicked: deleteClicked()
    }
}
