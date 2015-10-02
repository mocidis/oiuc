#!/bin/bash
for f in "/root/workspace/ics-project/oiuc/mockup/*.qml";
do
	sed -i 's/QtQuick 2.0/QtQuick 1.1/g' $f
done;

