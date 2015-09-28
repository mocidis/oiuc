import QtQuick 2.0

Flow {
    flow: Flow.TopToBottom
    anchors {
        fill: parent
    }
    Rectangle {
        width: parent.width
        height: parent.width/3
        radius: 10
        border {
            width: 2
            color: "black"
        }
        Rectangle {
            anchors {
                top: parent.top
                left: parent.left
                bottom: parent.bottom
                right: parent.right
                topMargin: 10
                rightMargin: 70
                leftMargin: 70
                bottomMargin: 70
            }
            radius: 3
            border {
                width: 1
                color: "black"
            }
        }
        Rectangle {
            width: 50
            height: 50
            radius: 25
            border {
                width: 1
                color: "black"
            }
            anchors {
                left: parent.left
                bottom: parent.bottom
                margins: 10
            }
        }
        Rectangle {
            id:ptt
            width: parent.width / 2
            height: 50
            radius: 10
            color: "#FF4444"
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
                bottomMargin: 10
            }
            Text {
                anchors {
                    centerIn:parent
                }
                text: "Push-to-talk"
                font {
                    pointSize: 18
                    bold: true;
                }
                color: "white"
            }
        }
        Rectangle {
            width: 50
            height: 50
            radius: 25
            border {
                width: 1
                color: "black"
            }
            anchors {
                right: parent.right
                bottom: parent.bottom
                margins: 10
            }
        }
    }
/*
    Rectangle {
        width: parent.width
        height: 20
        color: "transparent"
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
