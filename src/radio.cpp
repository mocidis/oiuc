#include "radio.h"
/*Constructor*/
Radio::Radio() {
	_name = "default";
	
}
Radio::Radio(QString name) {
	_name = name;	
}
Radio::Radio(QString name, double frequency, QString location, QString port_mip, int port, QString desc, bool isOnline, bool isTx, bool isSQ) {
	_name = name;
	_frequency = frequency;
	_location = location;
	_port_mip = port_mip;
	_port = port;
	_desc = desc;
    _isOnline = isOnline;
    _isTx = isTx;
    _isRx = false;
    _isSQ = isSQ;
    _volume = 0.5;
}

/*Add and set function*/

void Radio::setDowntime(double downtime) {
	_downtime = downtime;
	//emit signal if downtime occured
}

bool Radio::isOnline() {
    return _isOnline;
}
bool Radio::isTx() {
    return _isTx;
}
bool Radio::isRx() {
    return _isRx;
}
bool Radio::isSQ() {
    return _isSQ;
}
double Radio::getVolume() {
    return _volume;
}

/*Get function*/
void Radio::setOnline(bool val) {
    _isOnline = val;
}
void Radio::setTx(bool val) {
    _isTx = val;
}
void Radio::setRx(bool val) {
    _isRx = val;
}
void Radio::setSQ(bool val) {
    _isSQ = val;
}
void Radio::setVolume(double val) {
    _volume = val;
}

QString Radio::getName() {
	return _name;
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
double Radio::getDowntime() {
	return _downtime;
}
int Radio::getPort() {
	return _port;
}
QString Radio::getDesc() {
	return _desc;
}
