import QtQuick 2.0
ToggleButton {
    property alias text: label.text
    property alias textSize: label.font.pointSize
    height: width
    Text {
        id: label
        anchors.centerIn: parent
        color: "gray"
        font {
            pointSize: 20
        }
    }
    border {
        width: 1
        color: "lightgray"
    }
}

