import QtQuick 1.1

Rectangle {
    property color borderBrightColor: "green"
    property color borderDarkColor: "green"
    property color backgroundColor: "yellow"
    property color textColor: "blue"
    property int borderWidth: 4
	property alias text: label.text
	property alias textFontSize: label.font.pointSize
	property alias source: image.source

    id: outer

    signal clicked()

    height: width
    //radius: 0.5 * width
	radius: 10

    border {
        width: 0
    }

    color: borderBrightColor
    //rotation: 30
    gradient: Gradient {
        GradientStop { position: 0.0; color: borderDarkColor }
        GradientStop { position: 0.5; color: borderBrightColor }
        GradientStop { position: 1.0; color: borderDarkColor }
    }

    Rectangle {
        id: inner

        anchors {
            fill: parent
            //margins: parent.borderWidth
        }
        
        color: backgroundColor

		//radius: 0.5*width
		radius: 10
		smooth: true
    }

    MouseArea {
        id: mouseArea
        anchors {
            fill: parent
        }
        onReleased: {
            parent.clicked()
        }
    }
	Image {
		id: image	
		anchors.centerIn: parent
		smooth: true
		clip: true
		fillMode: Image.PreserveAspectFit
		width: 50; height: 50
	}
    Text {
        id: label

        //text: "t"
        color: parent.textColor
        font {
            family: "Futura"
            pointSize: 24
        }
        anchors {
            centerIn: parent
        }
        //rotation: -30
		smooth: true
    }
    state: "NORMAL"
    states: [
        State {
            name: "NORMAL"
            when: mouseArea.pressed == false
            PropertyChanges {
                target:inner
                color: outer.backgroundColor
            }
        },
        State {
            name: "PRESSED"
            when: mouseArea.pressed == true
            PropertyChanges {
                target:inner
                color: "lightgray"
            }
        }
    ]
/*
    transitions: Transition {
        from: "PRESSED"
        to: "NORMAL"
        ColorAnimation { duration: 200 }
    }
*/
}
