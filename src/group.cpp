#include "group.h"
#include "log.h"
/*Constructor*/
Group::Group() {
	_name = "DGroup";
	_status = "offline";
}
Group::Group(QString name, QString radio_list_str, QString status) {
	_name = name;
	_radio_list_str = radio_list_str;
	_status = status;
	_avaiable = 0;
	_desc = "NA";
	writeLog("Create new group");
}
Group::Group(QString name, QString radio_list_str, QString status, QString desc) {
	_name = name;
	_radio_list_str = radio_list_str;
	_status = status;
	_avaiable = 0;
	_desc = desc;
	writeLog("Create new group");
}
Group::Group(QString name, QString radio_list_str, QString status, int avaiable, QString desc) {
	_name = name;
	_radio_list_str = radio_list_str;
	_status = status;
	_avaiable = avaiable;
	_desc = desc;
	writeLog("Loading group from databases");
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
void Group::setStatus(QString status) {
	_status = status;
}
void Group::setAvaiable(int avaiable) {
	_avaiable = avaiable;
}
void Group::setDesc(QString desc) {
	_desc = desc;
}
/*******************Get functions********************/
QList<Radio*> Group::getRadioList() {
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
QString Group::getStatus() {
	return _status;
}
int Group::getAvaiable() {
	return _avaiable;
}
QString Group::getDesc() {
	return _desc;
}
