import QtQuick 2.0

Rectangle {
    property alias text: intext.text
    property alias align: intext.horizontalAlignment
    property alias font: intext.font
    width: parent.width
    height: 20
    color: "transparent"
    Text {
        id: intext
        text: "Radios"
        width: parent.width
        horizontalAlignment: Text.AlignRight
        anchors {
            top: parent.top
            left: parent.left
        }
        font {
            italic: true
        }
    }
    Rectangle {
        height: 1
        color: "#B0B0B0"
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }
}
