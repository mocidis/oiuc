import QtQuick 2.0

PanelCommon {
    id: root
    clip: true
    function hShow(rIdx, cIdx) {
        hStrip.y = 0 - root.height * rIdx
        hStrip.x = 0 - root.width * cIdx;
    }
    Flow {
        id: hStrip
        flow: Flow.TopToBottom
        spacing: 0
        Flow {
            Repeater {
                model: root.parent.radios
                delegate: ScreenRadio {
                    width: root.width
                    height: root.height
                    //tName: name
                    //tDesc: description
                    //port: port
                }
            }
        }
        Flow {
            Repeater {
                model: root.parent.oius
                delegate: ScreenOIU {
                    width: root.width
                    height: root.height
                    Text {
                        text: name + " " + index;
                    }
                }
            }
        }
        Flow {
            Repeater {
                model: root.parent.oius
                delegate: ScreenGroup {
                    color: "Pink"
                    width: root.width
                    height: root.height
                    Text {
                        text: name + " " + index;
                    }
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
