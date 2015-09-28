import QtQuick 2.0
Rectangle {
	width: 1366 
    height: 680
    color: "black"
    property ModelRadios radios : ModelRadios { }
    property ModelOIUs oius: ModelOIUs { }
    property ModelGroups groups: ModelGroups { }
    PanelTop {
        id: panelTop
        anchors {
            top: parent.top
            left: parent.left
            right: panelRight.right
        }
    }
    PanelLeft {
        id: panelLeft
        panel: panelMain
        width: parent.width * 0.18
        anchors {
            top: panelTop.bottom
            left: parent.left
            bottom: parent.bottom
        }
    }
    PanelMain {
        id: panelMain
        width: parent.width * 0.40
        anchors {
            top: panelTop.bottom
            left: panelLeft.right
            bottom: parent.bottom
            leftMargin: 1
        }
    }
    PanelRight {
        id: panelRight
        anchors {
            top: panelTop.bottom
            right: parent.right
            left: panelMain.right
            bottom: parent.bottom
            leftMargin: 1
        }
        MouseArea {
            anchors.fill: parent
            onClicked: panelRight.log("add one line");
        }
    }
}
