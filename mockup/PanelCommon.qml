import QtQuick 2.0

Flickable {
    property alias color: background.color
    Rectangle {
        id: background
        anchors.fill: parent
        color: "White"
    }
}
