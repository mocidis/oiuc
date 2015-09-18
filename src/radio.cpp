#include "radio.h"
/*Constructor*/
Radio::Radio() {
	_name = "default";
	
}
Radio::Radio(QString name) {
	_name = name;	
}
Radio::Radio(QString name, QString status, double frequency, QString location, QString port_mip, int avaiable) {
	_name = name;
	_status = status;
	_frequency = frequency;
	_location = location;
	_port_mip = port_mip;
	_avaiable = avaiable;
}

/*Add and set function*/

void Radio::setDowntime(QString downtime) {
	_downtime = downtime;
	//emit signal if downtime occured
}
void Radio::setStatus(QString status) {
	_status = status;
}
void Radio::setIState(int iState) {
	_iState = iState;
	//qDebug() << "++++++++++" << iState;
}
void Radio::setAvaiable(int avaiable) {
	_avaiable = avaiable;
}


/*Get function*/
QString Radio::getName() {
	return _name;
}

QString Radio::getRadioInfo() {
	QString info;
	info = _name + "\n" + _status + "\n" + QString::number(_frequency) + "\n" + _location; 
	return info;
}

QString Radio::getStatus() {
	return _status;
}
int Radio::getIState() {
	return _iState;
}
int Radio::getAvaiable() {
	return _avaiable;
}
