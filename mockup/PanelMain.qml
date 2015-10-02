import QtQuick 2.0

PanelCommon {
    id: root
    clip: true
    function hShow(rIdx, cIdx) {
//        console.log("Show " + rIdx + ":" + cIdx);
        hStrip.y = 0 - root.height * (rIdx + 1)
        hStrip.x = 0 - root.width * cIdx;
    }
    Flow {
        id: hStrip
        flow: Flow.TopToBottom
        spacing: 0
        Flow {
            ScreenHome {
                width: root.width
                height: root.height
            }
            /*ScreenAudio {
                width: root.width
                height: root.height
            }*/
            ScreenTelephone {
                width: root.width
                height: root.height
            }
            ScreenManageGroups {
                width: root.width
                height: root.height
            }
        }
        Flow {
            Repeater {
                id: radioRepeater
                model: _ROOT.models[0]
                delegate: ScreenRadio {
                    width: root.width
                    height: root.height
                    oModelItem: radioRepeater.model.get(index)
                }
            }
            Rectangle {
                width: root.width
                height: root.height
            }
        }
        Flow {
            Repeater {
                model: _ROOT.models[1]
                delegate: ScreenOIU {
                    width: root.width
                    height: root.height
                    Text {
                        text: name + " " + index;
                    }
                }
            }
            Rectangle { 
                width: root.width
                height: root.height
            }
        }
        Flow {
            Repeater {
                model: _ROOT.models[2]
                delegate: ScreenGroup {
                    width: root.width
                    height: root.height
                    oModelItem: _ROOT.models[2].get(index)
                }
            }
        }
        Behavior on x {
            NumberAnimation {
                duration: 100
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: 100
            }
        }
    }
}
