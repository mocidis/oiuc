import QtQuick 1.1
Item {
	property int itemHeight : 100
	property int itemWidth : 150
	property int logWidth: 150
	id: root
	width: 1366; height: 680
	TabController {
		id: endpointPanel
		columns: 2 // 0= vertical ; 1 = horizontal
		itemWidth: parent.itemWidth  * 0.5
		width: parent.itemWidth + 20
		height: parent.height - parent.itemHeight -1
		spacing: 8
		onChildClicked: {
			logPanel.writeLog("child clicked");
		}
		onDoThing: {
			item.onControlled(false);
		}
		border {
			width:1
			color:"black"
		}
		anchors {
			left: parent.left
			top:parent.top
		}
		innerAnchors {
			top: endpointPanel.top
			horizontalCenter: endpointPanel.horizontalCenter
			topMargin: 5
		}
		model: tabButtons
        VisualItemModel {
            id: tabButtons
			Repeater {	//endpointPanel button for Radio
				id: buttonRadio	
				model: modelRadio
				RectRadio {
					width: endpointPanel.itemWidth
					height: width
					text: modelData.getName();
					iIndex: index
					eContainer: endpointPanel
					eTabs: slidingWindow
					onSClicked: {
						if( _iState == 2 ) {
							eContainer.iterate(buttonRadio);
							onControlled(true);
							eTabs.showTab(iIndex);
						}
					}
				}
			}
			Repeater { 	//endpointPanel button for Group
				id: buttonGroup
				model: modelGroup
				RectRadio {
					width: endpointPanel.itemWidth
					height: width
					text: modelData.getName();
					iIndex: index
					eContainer: endpointPanel
					eTabs: slidingWindow
					onSClicked: {
						if( _iState == 2 ) {
							eContainer.iterate(buttonGroup);
							onControlled(true);
							eTabs.showTab(iIndex + buttonRadio.count);
						}
					}
				}
			}
			RectRadio {	//endpointPanel PSTN button
				id: buttonPSTN
				width: endpointPanel.itemWidth
				height: width
				text: "PSTN"
				eContainer: endpointPanel
				eTabs: slidingWindow
				onSClicked: {
					if( _iState == 2 ) {
						eContainer.iterate(buttonPSTN)
						onControlled(true);
						eTabs.showTab(buttonRadio.count + buttonGroup.count);
					}
				}
			}
        }
	}
	TabArray {
		id: slidingWindow
		anchors {
			top: parent.top
			left: endpointPanel.right
			bottom: statusPanel.top
			right: logPanel.left
			leftMargin: 2
			bottomMargin: 2
			rightMargin: 2
			
			//horizontalCenter: parent.horizontalCenter
			//verticalCenter: parent.verticalCenter
		}
		//clip: false
		//width: ( parent.width - endpointPanel.width - logPanel.width )/10
		//height: (parent.height - statusPanel.height)/10
		VisualItemModel {
			id: tabs
			Repeater {
				model: modelRadio
				ScreenRadio {
					width: slidingWindow.width
					height: slidingWindow.height
					//text: modelData.getName()
					text: modelData.getRadioInfo()
					color: "orange"
				}
			}
			Repeater {
				model: modelGroup
				id: screenGroupRe
				ScreenGroup {
					width: slidingWindow.width
					height: slidingWindow.height
					text: modelData.getName()
					screenGroup: screenGroupRe
					sIndex: index
					Grid{
						Repeater {
							model: modelData.getRadioList() //modelData of modelGroup
							Rectangle {
								width: 70; height: 70
								Text {
									text: modelData.getRadioInfo() //child model of modelGroup
								}
							}
						}
					}
					color: "orange"
				}
			}
			ScreenPSTN {
				width: slidingWindow.width 
				height: slidingWindow.height
			}
		}
		VisualItemModel {
			id: vTabs
			ScreenCommon {
				width: slidingWindow.width
				height: slidingWindow.height
				text: "About Us"
				color: "green"
			}
			ScreenCommon {
				width: slidingWindow.width
				height: slidingWindow.height
				text: "time settings"
				color: "yellow"
			}
			ScreenCommon {
				width: slidingWindow.width
				height: slidingWindow.height
				text: "speaker settings"
				color: "red"
			}
			ScreenCommon {
				width: slidingWindow.width
				height: slidingWindow.height
				text: "Microphone configs"
				color: "blue"
			}
			ScreenGroupConfig {
				width: slidingWindow.width
				height: slidingWindow.height
				//itemWidth: endpointPanel.itemWidth
				itemWidth: 100
				sWindow: slidingWindow
				spacing: 15
			}
			ScreenCommon {
				width: slidingWindow.width
				height: slidingWindow.height
				text: "PTT"
				color: "green"
			}
		}
		hModel: tabs
		vModel: vTabs
	}

	TabController {
		id: statusPanel
		width: parent.width
		height: parent.itemHeight + 3
		//columns: 1 // 0= vertical ; 1 = horizontal
		spacing: 5
		rows: 1
		columns: 6
		border {
			width:1
			color:"black"
		}
		anchors {
			left: parent.left
			bottom: parent.bottom
		}
		innerAnchors {
			left: statusPanel.left
			verticalCenter: statusPanel.verticalCenter
		}
		VisualItemModel {
			id: statusButton
			RectCommonButton {
				source: "../static/logo.jpg"
				description: "About Us"
				height: itemHeight
				iIndex: 0
				eContainer: endpointPanel
				eTabs: slidingWindow
			}
			DateTime {

			}
			RectCommonButton {
				source: "../static/Speaker-fill-black-small.svg"
				description: "Speaker"	
				iIndex: 2
				eContainer: endpointPanel
				eTabs: slidingWindow
			}
			RectCommonButton {
				source: "../static/Mic-fill-black-small.svg"
				description: "Microphone"
				iIndex: 3
				eContainer: endpointPanel
				eTabs: slidingWindow
			}
			RectCommonButton {
				source: "../static/group-fill-black.svg"
				description: "Group Config"
				iIndex: 4
				eContainer: endpointPanel
				eTabs: slidingWindow
			}
			RectCommonButton {
				id: pttButton
				source: "../static/ptt-fill-black.svg"
				description: "PTT"
				iIndex: 5
				eContainer: endpointPanel
				eTabs: slidingWindow
				MouseArea {
					anchors.fill: pttButton
					onClicked: {
						pttButton.pressed = true
						pttButton.pressed = false
						console.log("clicked 2");
					}
					onPressed: {
						pttButton.pressed = true
						console.log("pressed")
					}
				}
			}
		
		}
		model: statusButton

	}
	PanelLog {
		id: logPanel
		width: parent.logWidth
		height: parent.height - statusPanel.height
		anchors {
			top: parent.top
			right: parent.right
		}
	}
}