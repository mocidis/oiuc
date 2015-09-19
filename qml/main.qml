import QtQuick 1.1
Item {
	property int itemHeight : 100
	property int itemWidth : 150
	property int logWidth: 150
	property variant pttCurrent //current object that in controlled mode
	property int typeOfCurrentPTT
	Connections {
		target: ptt
	}
	id: root
	width: 1366; height: 680
	TabController {
		id: endpointPanel
		columns: 1
		itemWidth: parent.itemWidth  * 0.5
		width: parent.itemWidth + 20
		height: parent.height - parent.itemHeight - 1
		spacing: 8
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
			left: endpointPanel.left
			horizontalCenter: endpointPanel.horizontalCenter
			topMargin: 5
			leftMargin: 5
		}
		model: allButton
		VisualItemModel {
			id: allButton
			TabController {
				id: radioButton
				columns: 2
				spacing: 5
				model: radioPanel
				width: endpointPanel.width - 10; height: Math.ceil(buttonRadio.count/2) * endpointPanel.itemHeight + radioButton.spacing*Math.ceil(buttonRadio.count/2);
				VisualItemModel {
					id: radioPanel
					Repeater {	//endpointPanel button for Radio
					id: buttonRadio	
					model: modelRadio
					RectRadio {
						width: endpointPanel.itemWidth
						height: width
						text: modelData.getName();
						iIndex: index
						iState: modelData.getIState()
						//eContainer: endpointPanel
						eContainer: radioButton
						eTabs: slidingWindow
						onSClicked: {
							if( _iState == 2 ) {
								//eContainer.iterate(buttonRadio);
								var var_count;
								for (var_count = 0; var_count < buttonRadio.count; var_count++) {
									if (modelRadio[var_count].getIState() == 2) {
										modelRadio[var_count].setIState(modelRadio[var_count].getIState()-1);
									}
								}
								endpointPanel.iterate(buttonGroup);
								endpointPanel.iterate(buttonRadio);
								endpointPanel.iterate(buttonOIUC);
								onControlled(true);
								modelData.setIState(2);
								pttCurrent = modelData;
								typeOfCurrentPTT = 0;
								eTabs.showTab(iIndex);
							}
						}
						onSLongClicked: {
							modelData.setIState(iState);
						}
					}
				}
			}
		}
		TabController {
			id: oiucButton
			columns: 2
			spacing: 5
			model: oiucPanel
			width: endpointPanel.width - 10; height: Math.ceil(buttonOIUC.count/2) * endpointPanel.itemHeight + oiucButton.spacing*Math.ceil(buttonOIUC.count/2);
			VisualItemModel {
				id: oiucPanel
				Repeater {	//endpointPanel button for Radio
				id: buttonOIUC
				model: modelOIUC
				RectRadio {
					iState: modelData.getIState()
					width: endpointPanel.itemWidth
					height: width
					text: modelData.getName();
					iIndex: index
					//eContainer: endpointPanel
					eContainer: oiucButton
					eTabs: slidingWindow
					onSClicked: {
						if( iState == 2 ) {
							//eContainer.iterate(buttonRadio);
							var var_count;
							for (var_count = 0; var_count < buttonOIUC.count; var_count++) {
								if (modelOIUC[var_count].getIState() == 2) {
									modelOIUC[var_count].setIState(modelOIUC[var_count].getIState()-1);
								}
							}
							endpointPanel.iterate(buttonRadio);
							endpointPanel.iterate(buttonOIUC);
							endpointPanel.iterate(buttonGroup);
							onControlled(true);
							modelData.setIState(2);
							pttCurrent = modelData;
							typeOfCurrentPTT = 1;
							eTabs.showTab(iIndex + buttonRadio.count);
						}
					}
					onSLongClicked: {
						modelData.setIState(iState);
					}
				}
			}
		}
	}
	TabController {
		id: groupButton
		columns: 2
		spacing: 5
		model: groupPanel
		width: endpointPanel.width - 10; height: Math.ceil(buttonGroup.count/2) * endpointPanel.itemHeight + groupButton.spacing*Math.ceil(buttonGroup.count/2);
		VisualItemModel {
			id: groupPanel
			Repeater { 	//endpointPanel button for Group
			id: buttonGroup
			model: modelGroup
			RectRadio {
				width: endpointPanel.itemWidth
				height: width
				text: modelData.getName();
				iIndex: index
				iState: modelData.getIState()
				eContainer: groupButton
				eTabs: slidingWindow
				onSClicked: {
					if( _iState == 2 ) {
						//eContainer.iterate(buttonGroup);
						var var_count;
						for (var_count = 0; var_count < buttonGroup.count; var_count++) {
							if (modelGroup[var_count].getIState() == 2) {
								modelGroup[var_count].setIState(modelGroup[var_count].getIState()-1);
							}
						}
						endpointPanel.iterate(buttonGroup);
						endpointPanel.iterate(buttonRadio);
						endpointPanel.iterate(buttonOIUC);
						onControlled(true);
						modelData.setIState(2);
						pttCurrent = modelData;
						typeOfCurrentPTT = 2;
						eTabs.showTab(iIndex + buttonRadio.count + buttonOIUC.count);
					}
				}
				onSLongClicked: {
					modelData.setIState(iState);
				}
			}
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
			model: modelOIUC
			ScreenRadio {
				width: slidingWindow.width
				height: slidingWindow.height
				//text: modelData.getName()
				text: modelData.getOIUCInfo()
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
	}
	VisualItemModel {
		id: vTabs
		ScreenCommon {
			width: slidingWindow.width
			height: slidingWindow.height
			text: "About Us"
			color: "white"
		}
		ScreenCommon {
			width: slidingWindow.width
			height: slidingWindow.height
			text: "time settings"
			color: "white"
		}
		ScreenCommon {
			width: slidingWindow.width
			height: slidingWindow.height
			text: "speaker settings"
			color: "white"
		}
		ScreenCommon {
			width: slidingWindow.width
			height: slidingWindow.height
			text: "Microphone configs"
			color: "white"
		}
		ScreenPSTN {
			width: slidingWindow.width 
			height: slidingWindow.height
		}
		ScreenGroupConfig {
			width: slidingWindow.width
			height: slidingWindow.height
			//itemWidth: endpointPanel.itemWidth
			itemWidth: 100
			sWindow: slidingWindow
			spacing: 15
			color: "white"
		}
		//ScreenCommon {
			//width: slidingWindow.width
			//height: slidingWindow.height
			//text: "PTT"
			//color: "white"
		//}
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
	columns: 7
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
			source: "../static/pstn-fill-black.svg"
			description: "PSTN"
			iIndex: 4
			eContainer: endpointPanel
			eTabs: slidingWindow
		}
		RectCommonButton {
			source: "../static/group-fill-black.svg"
			description: "Group Config"
			iIndex: 5
			eContainer: endpointPanel
			eTabs: slidingWindow
		}
		RectCommonButton {
			id: pttButton
			source: "../static/ptt-fill-black.svg"
			description: "PTT"
			iIndex: 6
			eContainer: endpointPanel
			eTabs: slidingWindow
			MouseArea {
				anchors.fill: pttButton
				onClicked: {
					pttButton.pressed = true
					pttButton.pressed = false
				}
				onEntered: {
					pttButton.pressed = true;
					if (pttCurrent != null) {
						ptt.setPTT(pttCurrent, typeOfCurrentPTT, 1);
					}
				}
				onExited: {
					ptt.setIsPressedPTT(0);
					pttButton.pressed = false
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
