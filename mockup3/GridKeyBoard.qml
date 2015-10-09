import QtQuick 1.1

Grid {
    property int itemSize: 80
    property int itemMargin: 10
    property alias spacing: grid.spacing
    property alias columns: grid.columns
    property alias rows: grid.rows
    property color borderBrightColor: "white"
    property color borderDarkColor: "gray"
    property color backgroundColor: "#002000"
    property color textColor: "white"
    signal clicked(string label)
    id: grid
    anchors {
        fill: parent
    }
    columns: 3
    rows: 4
    Repeater {
        model: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "CLR", "0", "RDL"]
        CirclePushButton {
            borderBrightColor: parent.borderBrightColor
            borderDarkColor: parent.borderDarkColor
            borderWidth: 2
            backgroundColor: parent.backgroundColor
            textColor: parent.textColor

            width: parent.itemSize
            text: modelData
            onClicked: {
                parent.clicked(text);
            }
        }
    }
}
