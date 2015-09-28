#include "oiuc.h"
/*Constructor*/
OIUC::OIUC() {
	_name = "default";
}
OIUC::OIUC(QString name) {
	_name = name;
}
OIUC::OIUC(int msg_id, QString type, QString name, QString  status) {
	_msg_id = msg_id; 
	_type = type;
	_name = name;
	_status = status;
	_iState = 0;
}

/*Add and set function*/
void OIUC::setDowntime(QString downtime) {
	_downtime = downtime;
	//emit signal if downtime occured
}
void OIUC::setStatus(QString status) {
	_status = status;
}
void OIUC::setIState(int iState) {
	_iState = iState;
}


/*Get function*/
QString OIUC::getName() {
	return _name;
}

QString OIUC::getOIUCInfo() {
	QString info;
	info = _name + "\n" + _status;
	return info;
}

QString OIUC::getStatus() {
	return _status;
}
int OIUC::getIState() {
	return _iState;
}
