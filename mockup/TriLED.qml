import QtQuick 2.0
TriLEDCommon {
    property int itemWidth: 6
    spacing: 2
    red: redRect
    green: greenRect
    yellow: yellowRect
    Rectangle {
        id: redRect
        width: itemWidth
        height: width
        color: dimColor
    }
    Rectangle {
        id: yellowRect
        width: itemWidth
        height: width
        color: dimColor
    }
    Rectangle {
        id: greenRect
        width: itemWidth
        height: width
        color: dimColor
    }
}
