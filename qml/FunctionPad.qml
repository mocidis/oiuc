import QtQuick 1.1
Item {
	id: func_pad
	property int itemSize: 80
	property int textSize: 14
	property alias spacing: grid.spacing
	property alias columns: grid.columns
	signal clicked(string value)
	Grid {
		id: grid
		anchors.fill: parent
		columns: 2
		spacing: 30
		Repeater {
			model: ["Call", "Ha", "Ha all", "Trans", "Conf", "Answer"]
			CirclePushButton {
				text: modelData
				onClicked: {
					func_pad.clicked(text)
				}
            	borderBrightColor: "white"
            	borderDarkColor: "gray"
            	borderWidth: 2
            	backgroundColor: "#003000"
				textColor: "White"
				textFontSize: textSize

            	width: itemSize
			}
		}
	}
}
