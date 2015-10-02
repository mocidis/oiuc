import QtQuick 2.0
Flow {
    property color dimColor: "gray"
    property variant oModelItem: null
    property variant red: null
    property variant green: null
    property variant yellow: null
    
    function setRed(booleanVal) {
        if (oModelItem == null) return;
        oModelItem.isRed = booleanVal;
    }
    function setGreen(booleanVal) {
        if (oModelItem == null) return;
        oModelItem.isGreen = booleanVal;
    }
    function setYellow(booleanVal) {
        if (oModelItem == null) return;
        oModelItem.isYellow = booleanVal;
    }
    StateGroup {
        states: [
            State {
                name: "RED"
                when: (oModelItem != null) && (oModelItem.isRed)
                PropertyChanges {target: red; color:"red"}
            }
        ]
    }
    StateGroup {
        states: [
            State {
                name: "GREEN"
                when: (oModelItem != null) && (oModelItem.isGreen)
                PropertyChanges {target: green; color:"lime"}
            }
        ]
    }
    StateGroup {
        states: [
            State {
                name: "YELLOW"
                when: (oModelItem != null) && (oModelItem.isYellow)
                PropertyChanges {target: yellow; color: "yellow"}
            }
        ]
    }
}
