import QtQuick 1.1
Item {
	id: func_pad
	property int itemSize: 60
	property int textSize: 14
	property alias spacing: grid.spacing
	property alias columns: grid.columns
    width: grid.width
    height: grid.height
	signal clicked(string value)
	Grid {
		id: grid
		columns: 2
		spacing: 20
		Repeater {
			model: ["Call", "Ha", "Ha all", "Trans", "Conf", "Answer"]
			CirclePushButton {
				onClicked: {
					func_pad.clicked(text)
				}
                text: modelData
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
