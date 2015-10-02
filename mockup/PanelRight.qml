import QtQuick 2.0

PanelCommon {
    function log(line) {
        logContent.text = logContent.text + "\n" + line
    }
    Text {
        id: logContent
        color: "red"
        anchors.fill: parent
        anchors.margins: 10
        text: "Lorem ipsum dolor sit amet"
    }
}
