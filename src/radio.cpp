#include "radio.h"
/*Constructor*/
Radio::Radio() {
	_name = "default";
	
}
Radio::Radio(QString name) {
	_name = name;	
}
Radio::Radio(QString name, QString status, double frequency, QString location) {
	_name = name;
	_status = status;
	_frequency = frequency;
	_location = location;
}

/*Add and set function*/



/*Get function*/
QString Radio::getName() {
	return _name;
}

QString Radio::getRadioInfo() {
	QString info;
	info = _name + "\n" + _status + "\n" + QString::number(_frequency) + "\n" + _location; 
	return info;
}
