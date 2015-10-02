#include "radio.h"
/*Constructor*/
Radio::Radio() {
	_name = "default";
	
}
Radio::Radio(QString name) {
	_name = name;	
}
Radio::Radio(QString name, QString status, double frequency, QString location, QString port_mip, int avaiable, int port) {
	_name = name;
	_status = status;
	_frequency = frequency;
	_location = location;
	_port_mip = port_mip;
	_avaiable = avaiable;
	_port = port;
}

/*Add and set function*/

void Radio::setDowntime(QString downtime) {
	_downtime = downtime;
	//emit signal if downtime occured
}
void Radio::setStatus(QString status) {
	_status = status;
}
void Radio::setAvaiable(int avaiable) {
	_avaiable = avaiable;
}


/*Get function*/
QString Radio::getName() {
	return _name;
}

QString Radio::getStatus() {
	return _status;
}

int Radio::getAvaiable() {
	return _avaiable;
}
double Radio::getFrequency() {
	return _frequency;
}
QString Radio::getLocation() {
	return _location;
}
QString Radio::getPortMIP() {
	return _port_mip;
}
QString Radio::getDowntime() {
	return _downtime;
}
int Radio::getPort() {
	return _port;
}
