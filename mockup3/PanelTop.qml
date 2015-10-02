import QtQuick 1.1

PanelCommon {
    property int itemWidth: 120
    id: root
    height: 45
    color: "#F0F0F0"
    Flow {
        id: menu
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
            //margins: 15
        }
        spacing: 5
        PushButton {
            color: "transparent"
            width: home.width + 60
            height: root.height
            Text {
                id: home
                anchors.centerIn: parent
                text: "Home"
            }
            onClicked: _ROOT.main.hShow(-1, 0)
        }
        //PushButton {
            //color: "transparent"
            //width: audio.width + 60
            //height: root.height
            //Text {
                //id: audio
                //anchors.centerIn: parent
                //text: "Audio"
            //}
            //onClicked: _ROOT.main.hShow(-1, 1)
        //}
        PushButton {
            color: "transparent"
            width: pstn.width + 60
            height: root.height
            Text {
                id: pstn
                anchors.centerIn: parent
                text: "Telephone"
            }
            onClicked: _ROOT.main.hShow(-1, 1)
        }
        PushButton {
            color: "transparent"
            width: manageGroups.width + 60
            height: root.height
            Text {
                id: manageGroups
                anchors.centerIn: parent
                text: "Manage groups"
            }
            onClicked: _ROOT.main.hShow(-1, 2)
        }
    }
	FontLoader {id: lcdFont; source: "../static/fonts/digital-7.ttf"}
    Text {
        id: time
        anchors {
            top: parent.top
            right: parent.right
            bottom: parent.bottom
            margins: 15
        }
        text: "--/--/--"
		font.family: lcdFont.name
		font.pixelSize: 16 
		font.letterSpacing: 3
        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: parent.text = Qt.formatDateTime(new Date(), "hh:mm:ss -- dd/MM/yyyy")
        }
    }
    Rectangle {
        height: 1
        color: "black"
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
