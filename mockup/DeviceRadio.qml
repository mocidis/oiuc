import QtQuick 2.0

Flow {
    property alias oModelItem: indicator.oModelItem
    function getName() {
        if (oModelItem == null) return "NaN";
        return oModelItem.name;
    }
    function getDesc() {
        if (oModelItem == null) return "NaN";
        return oModelItem.description;
    }
    function getPort() {
        if (oModelItem == null) return -1;
        return oModelItem.port;
    }

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
            height: parent.height * 0.45
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
                anchors {
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }
                width: parent.width / 5
            }
            Rectangle {
                width: parent.width/2
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
                            text: "CH " + getPort()
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
                            pointSize: 10
                            italic: true
                        }
                    }
                }
            }
            PushButton {
                id:ptt
                width: parent.width / 5
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                }
                radius: 10
                color: "#BB0000"
                Text {
                    anchors {
                        centerIn:parent
                    }
                    text: "PTT"
                    font {
                        pointSize: 18
                        bold: true;
                    }
                    color: "white"
                }
            }
        }
        Rectangle {
            height: 50
            width: 200
            radius: 8
            border {
                width: 1
                color: "black"
            }
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
                normalSource: "../static/Speaker-fill-black-small.svg"
                muteSource: "../static/Speaker-mute-fill-black-small.svg"
            }
        }
        Rectangle {
            height: 50
            width: 200
            radius: 8
            border {
                width: 1
                color: "black"
            }
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
                normalSource: "../static/Mic-fill-black-small.svg"
                muteSource: "../static/Mic-mute-fill-black-small.svg"
            }
        }
    }
    Rectangle {
        width: parent.width
        height: 5
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
}
