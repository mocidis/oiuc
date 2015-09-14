import QtQuick 1.1

Rectangle {
    property alias hModel: tabs.model
    property alias vModel: vTabs.model
    property alias delegate: tabs.delegate

    width: 150
    height: 150
    color: "lightgray"
    clip: true

    Rectangle {
        id: slider
        width: parent.width * tabs.count; //Layout messing when resize window
        height: parent.height
        Column {
            Repeater {
                id: tabs
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: 0
            }
        }
	}
	Rectangle {
		id: vSlider
		width:parent.width
		height: parent.height
		y: parent.height
        Row {
            Repeater {
                id: vTabs
            }
        }
	}

	function showVTab(idx, bShown) { // for status panel
		//if( bShown ) vSlider.anchors.top = slider.top;
		//else vSlider.anchors.top = slider.bottom;
		
		if (bShown) {
			vSlider.x = 0 - width * idx
			vSlider.y = 0
			//vSlider.y = 0;
		}
		else {
			vSlider.x = width;
		}
		console.log("idx: " + idx + "....." + vSlider.y)
	}
	function showTab(idx) {
		showVTab(false, 0);
        slider.y = 0 - height * idx;
	}
}
