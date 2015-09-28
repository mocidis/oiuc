import QtQuick 2.0

PanelCommon {
    property PanelMain panel: null
    property ButtonCommon current: null
    id: root
    color: "#F0F0F0"
    Flow {
        flow: Flow.TopToBottom
        spacing: 10
        anchors {
            fill:parent
            margins: 10
        }
        Flow {
            width: parent.width
            flow: Flow.LeftToRight
            spacing: 20
            Repeater {
                id: radioRepeater
                model: root.parent.radios
                delegate: ButtonRadio { 
                    text: name + "." + port; 
                    panel: root.panel; 
                    modelIndex: 0; 
                    tabIndex: index 
                    onClicked: {
                        if( iState == 1 ) {
                            current = null;
                        }
                        else {
                            if( current != null ) current.toggleControlled();
                            current = radioRepeater.itemAt(index);
                        }
                    }
                }
            }
        }
        LabelCommon {
            text: "Radios"
        }
        Flow {
            width: parent.width
            flow: Flow.LeftToRight
            spacing: 20
            Repeater {
                id: oiuRepeater
                model: root.parent.oius
                delegate: ButtonOIU { 
                    text: name; 
                    panel:root.panel; 
                    modelIndex: 1;
                    tabIndex: index
                    onClicked: {
                        if( iState == 1 ) {
                            current = null;
                        }
                        else {
                            if( current != null ) current.toggleControlled();
                            current = oiuRepeater.itemAt(index);
                        }
                    }
                }
            }
        }
        LabelCommon {
            text: "Operators"
        }
        Flow {
            width: parent.width
            flow: Flow.LeftToRight
            spacing: 20

            Repeater {
                id: groupRepeater
                model: root.parent.groups
                delegate: ButtonGroup { 
                    text: name;
                    panel: root.panel;
                    modelIndex: 2;
                    tabIndex: index
                    onClicked: {
                        if( iState == 1 ) {
                            current = null;
                        }
                        else {
                            if( current != null ) current.toggleControlled();
                            current = groupRepeater.itemAt(index);
                        }
                    }
                }
            }
        }
        LabelCommon {
            text: "Groups"
        }
    }
}
