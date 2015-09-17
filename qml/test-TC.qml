import QtQuick 1.1

Rectangle {
	width: 600
	height: 400
	color: "transparent"
	TabController {
		id:tcs
		model: cpanels
		itemWidth: 20
		//itemHeight: 60
		anchors {
			left: parent.left
			top: parent.top
		}
		onChildClicked: {
			console.log("Child clicked\n");
		}
		onDoThing: {
			item.iterate();
		}
		VisualItemModel {
			id: cpanels
			TabController {
				id: tc1
				model: cbuttons1
				columns: 1
				itemWidth: 20
				width: getWidth()
				height:getHeight()
				color:"yellow"
				onDoThing: {
					item.thing();
				}
				VisualItemModel {
					id: cbuttons1
					Rectangle {
						width: tc1.itemWidth
						height: width
						color: "blue"
						MouseArea {
							anchors.fill: parent
							onClicked: {
								console.log("clicked on first button\n");
								tcs.iterate();
							}
						}
						function thing() {
							console.log("first control button");
						}
					}
					Rectangle {
						width: tc1.itemWidth
						height: width
						color: "green"
						MouseArea {
							anchors.fill: parent
							onClicked: {
								console.log("clicked on second button\n");
								tcs.iterate();
							}
						}
						function thing() {
							console.log("second control button");
						}
					}
					Rectangle {
						width: tc1.itemWidth
						height: width
						color: "red"
						MouseArea {
							anchors.fill: parent
							onClicked: {
								console.log("clicked on third button\n");
								tcs.iterate();
							}
						}
						function thing() {
							console.log("third control button");
						}
					}
				}
			}
			TabController {
				id: tc2
				model: cbuttons2
				columns: 1
				itemWidth: 20
				color:"yellow"
				width: getWidth()
				height: getHeight()
				onDoThing: {
					item.thing();
				}
				VisualItemModel {
					id: cbuttons2
					Rectangle {
						width: tc2.itemWidth
						height: width
						color: "blue"
						MouseArea {
							anchors.fill: parent
							onClicked: {
								console.log("clicked on 3 button\n");
								tcs.iterate();
							}
						}
						function thing() {
							console.log("3 control button");
						}
					}
					Rectangle {
						width: tc2.itemWidth
						height: width
						color: "Maroon"
						MouseArea {
							anchors.fill: parent
							onClicked: {
								console.log("clicked on 4 button\n");
								tcs.iterate();
							}
						}
						function thing() {
							console.log("4 control button");
						}
					}
					Rectangle {
						width: tc2.itemWidth
						height: width
						color: "red"
						MouseArea {
							anchors.fill: parent
							onClicked: {
								console.log("clicked on 5 button\n");
								tcs.iterate();
							}
						}
						function thing() {
							console.log("5 control button");
						}
					}
				}
			}
		} // VisualItemModel
	}
	TabArray {
		id: tabarray
		color: "maroon"
		width: parent.width - tc2.getWidth()
		anchors {
			bottom: parent.bottom
			right: parent.right
			top: parent.top
		}
		VisualItemModel {
			Rectangle {
				width: tabarray.width
				height: tabarray.height
				color: "lightgreen"
			}
			Rectangle {
				width: tabarray.width
				height: tabarray.height
				color: "pink"
			}
		}
	}
}
