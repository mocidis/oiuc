import QtQuick 1.1

PanelCommon {
    id: root
    ScreenHome {
        width: root.width
        height: root.height
    }
    Repeater {
        id: radioRepeater
        model: _ROOT.models[0]
        delegate: ScreenRadio {
            width: root.width
            height: root.height
            oModelItem: radioRepeater.model.get(index)
        }
    }
    Repeater {
        id: oiuRepeater
        model: _ROOT.models[1]
        delegate: ScreenOIU {
            width: root.width
            height: root.height
            oModelItem: oiuRepeater.model.get(index)
        }
    }
    Repeater {
        model: _ROOT.models[2]
        delegate: ScreenGroup {
            width: root.width
            height: root.height
            id: groupScreen
            oModelItem: _ROOT.models[2].get(index)
            contentHeight: Math.floor(nodes.count * 90 + 90)
            onDeleteClicked: {
                console.log("Group Delete");
                groupObj.deleteGroup(index);
            }
        }
    }
}
