import QtQuick 1.1
Rectangle {
    width: 300
    height: 600
    id: _ROOT
    property list<ListModel> models: [ ModelRadios{}, ModelOIUs{}, ModelGroups{} ]
    GroupManDialog {
        anchors {fill:parent}
    }
}
