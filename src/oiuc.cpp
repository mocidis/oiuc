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
}

/*Add and set function*/
void OIUC::setDowntime(QString downtime) {
	_downtime = downtime;
	//emit signal if downtime occured
}
void OIUC::setStatus(QString status) {
	_status = status;
}


/*Get function*/
QString OIUC::getName() {
	return _name;
}

QString OIUC::getStatus() {
	return _status;
}
QString OIUC::getType() {
	return _type;
}
QString OIUC::getDowntime() {
	return _downtime;
}
