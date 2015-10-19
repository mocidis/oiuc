import QtQuick 1.1

PanelCommon {
    property int itemWidth: 120
    id: root
    height: 50
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
        PushTextButton {
            color: "transparent"
            onColor: "navy"
            width: labelWidth + 60
            height: root.height
            label: "Home"
            labelColor: isPressed?"white":"black"
            onClicked: {
                _LOGINABOUTDIALOG.visible = true;
            }
        }
        PushTextButton {
            color: "transparent"
            onColor: "navy"
            width: labelWidth + 60
            height: root.height
            label: "Telephone"
            labelColor: isPressed?"white":"black"
            onClicked: { 
                _TELKB.visible = !_TELKB.visible;
            }
        }
    }
    Text {
        id: time
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            margins: 15
            rightMargin: 15 + 2*root.height
        }
        text: "--/--/--"
		font {
            family: lcdFont.name
		    pixelSize: 16 
		    letterSpacing: 3
        }
        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: parent.text = Qt.formatDateTime(new Date(), "hh:mm:ss -- dd/MM/yyyy")
        }
    }
    VolumeControl {
        id: speaker
        width: root.height
        height: root.height
        sourcePrefix: "../static/Speaker"
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: root.height
        }
        onClicked: {
            microphone.value = false;
            _SLIDER.object = value?speaker:null
        }
        oItem: QtObject {
            property double volume: 0.5
        }
    }
    VolumeControl {
        id: microphone
        width: root.height
        height: root.height
        sourcePrefix: "../static/Mic"
        anchors {
            top: parent.top
            right: parent.right
        }
        onClicked: {
            speaker.value = false;
            _SLIDER.object = value?microphone:null
        }
        oItem: QtObject {
            property double volume: 0.5
        }
    }
/*
    ToggleButton {
        property double rValue: 0.5
        id: speaker
        onColor: "white"
        color: "transparent"
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: root.height
        }
        width: root.height
        height: root.height
        Image {
            anchors { centerIn: parent }
            smooth: true
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            source: (parent.rValue > 0)?"../static/Speaker-fill-black-small.svg":"../static/Speaker-mute-fill-black-small.svg"
        }
        onClicked: {
            microphone.value = false;
            _SLIDER.object = value?speaker:null
        }
    }
    ToggleButton {
        property double rValue: 0.5
        id: microphone
        onColor: "white"
        color: "transparent"
        anchors {
            top: parent.top
            right: parent.right
        }
        width: root.height
        height: root.height
        Image {
            anchors { centerIn: parent }
            smooth: true
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
            source: (parent.rValue > 0)?"../static/Mic-fill-black-small.svg":"../static/Mic-mute-fill-black-small.svg"
        }
        onClicked: { 
            speaker.value = false; 
            _SLIDER.object = value?microphone:null;
        }
    }
*/
    Rectangle {
        height: 1
        color: "black"
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
    StateGroup {
        states: [
            State {
                name: "logout"
                when: (!_ROOT.appState.login) || _TELKB.visible
                PropertyChanges { target: menu; enabled: false }
            },
            State {
                name: "login"
                when: _ROOT.appState.login && !_TELKB.visible
                PropertyChanges { target: menu; enabled: true }
            }
        ]
    }
}
