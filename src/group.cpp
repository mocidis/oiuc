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
	_iState = 0;
	writeLog("Create new group");
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
void Group::setIState(int iState) {
	_iState = iState;
	//qDebug() << "++++++++++" << iState;
}
void Group::setAvaiable(int avaiable) {
	_avaiable = avaiable;
}

/*******************Get functions********************/
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
QString Group::getStatus() {
	return _status;
}
int Group::getIState() {
	return _iState;
}
