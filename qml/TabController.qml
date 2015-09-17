import QtQuick 1.1

Rectangle {
	property alias model: repeater.model
	property int itemWidth: 50
	property int itemHeight: itemWidth
    property alias spacing: grid.spacing
    property alias columns: grid.columns
	property alias innerAnchors: grid.anchors
	property alias rows: grid.rows
    id: root

	signal childClicked()
	signal doThing(variant item)
    function getHeight() {
        var rows = Math.ceil(repeater.count / grid.columns);
        return rows * itemHeight + (rows + 1) * spacing;
	}

	function getInternalRepeater() {
		return repeater;
	}

    function getWidth() {
        return grid.columns * itemWidth + (grid.columns + 1) * spacing;
    }

    function iterate( aRepeater ) { // Loop on aRepeater param or on repeater (default one)
		var j;
		var lRepeater = repeater;
		if( aRepeater != null && aRepeater != undefined ) lRepeater = aRepeater;
        for( j = 0; j < lRepeater.count; j++ ) {
			doThing( lRepeater.itemAt(j) );
            //doThing( aRepeater );
        }
    }

    Grid {
        id: grid
        columns: 1
        //rows: 3
		//anchors { 
			//centerIn: parent			
			//horizontalCenter: parent.horizontalCenter 
			//verticalCenter: parent.verticalCenter
		//}
        Repeater {
            id: repeater
        }
    }
}
