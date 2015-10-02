import QtQuick 1.1
Flickable {
    property alias color: background.color
    Rectangle {
        id: background
        anchors.fill: parent
        color: "White"
    }
}
