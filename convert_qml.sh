#!/bin/bash
if [ $# != 2 ]; then
	echo "Usage: $0 qml_directory direction"
	echo "Example: $0 mockup 12"
	echo "Example: $0 mockup 21"
	echo ""
	exit 0
fi
if [ $2 == "21" ]; then
	for f in "$1/*.qml";
	do
		sed -i 's/QtQuick 2.0/QtQuick 1.1/g' $f
	done;
elif [ $2 == "12" ]; then
	for f in "$1/*.qml";
	do
		sed -i 's/QtQuick 1.1/QtQuick 2.0/g' $f
	done;
fi
