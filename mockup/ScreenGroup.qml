import QtQuick 2.0
ScreenCommon {
    property variant oModelItem: null
    Flow {
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
                    font.pointSize: 24
                    font.bold: true
                    text: "Push-To-Talk"
                    color: "white"
                }
                onClicked : {
                    console.log("PTT button clicked");
                }
            }
        }
        Repeater {
            id: groupRepeater
            model: oModelItem.nodes
            DeviceRadioReduced {
                width: parent.width
                height: 90
                color: ( (index % 2) == 0 ) ? "#585858" : "#858585"
                oModelItem: _ROOT.models[modelIdx].get(itemIdx)
            }
        }
    }
}
