#include "group.h"
/*Constructor*/
Group::Group() {
	_name = "DGroup";
	_status = "offline";
}
Group::Group(QString name, QString radio_list_str, QString status) {
	_name = name;
	_radio_list_str = radio_list_str;
	_status = status;
}
/* Add and Set functions*/
void Group::addRadio(Radio *radio) {
	_radio_list.append(radio);
}
void Group::setRadioList(QList<Radio*> radio_list) {
	for (int i=0;i<radio_list.count(); i++) {
		_radio_list.append(radio_list[i]);
	}
}

/*Get functions*/
QList<QObject*> Group::getRadioList() {
	return _radio_list;
}
QString Group::getName () {
	return _name;
}
int Group::getRadioListSize() {
	return _radio_list.count();
}
QString Group::getRadioListStr() {
	return _radio_list_str;
}
QString Group::getGroupStatus() {
	return _status;
}
