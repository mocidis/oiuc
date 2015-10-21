#include "radio_manager.h"
#include "backend.h"
/*****************Constructor******************/
RadioManager* RadioManager::_radio_manager = 0;
RadioManager* RadioManager::getRadioManager() {
	if (_radio_manager == NULL) {
		_radio_manager = new RadioManager();
	}
	return _radio_manager;
}
RadioManager::RadioManager(QList<Radio*> radio_list) {
	_flag = false;	
}
RadioManager::RadioManager() {
	_flag = false;
}
/*****************Add and Set functions******************/
void RadioManager::loadRadioFromDatabase() {
	writeLog("Loading Radio from databases");
	_radio_list = getBackendRadioList("databases/radio.db");
	for (int i=0;i<_radio_list.count();i++) {
		updateRadioManagerSignal(_radio_list[i], -1);
	}
	_flag = true;
}
void RadioManager::addRadio(Radio *radio) {
	int flags = 0;
	int mIndex = -1;
	for (int i=0; i < _radio_list.count(); i++) {
		if (_radio_list[i]->getName() == radio->getName()) {
			flags = 1;
			if (_radio_list[i]->isOnline() != radio->isOnline()) {
				_radio_list[i]->setOnline(radio->isOnline());
				flags = 2;
				mIndex = i;
				qDebug() << "---------------------------------------";
			}
			if (_radio_list[i]->isTx() != radio->isTx()) {
				_radio_list[i]->setTx(radio->isTx());
				flags = 2;
				mIndex = i;
			}
			if (_radio_list[i]->isSQ() != radio->isSQ()) {
				_radio_list[i]->setSQ(radio->isSQ());
				flags = 2;
				mIndex = i;
			}
			break;
		}
	}
	if (flags == 0 || flags == 2) {
		if (flags == 0) {
			_radio_list.append(radio);
			appendToDatabase(radio, "databases/radio.db", 0);
			updateRadioManagerSignal(radio, mIndex);
			writeLog("new radio " + radio->getName() + " detected");
		} else {
			appendToDatabase(radio, "databases/radio.db", 1);
			updateRadioManagerSignal(radio, mIndex);
			writeLog(radio->getName() + " changed state");
		}
	}
}
void RadioManager::deleteRadio(Radio *radio) {
	for (int i=0;i<_radio_list.count();i++) {
		if (_radio_list[i]->getName() == radio->getName()) {
			_radio_list.removeAt(i);
		}
	}
}
/*****************Get functions******************/
QList<QObject*> RadioManager::getModelRadio() { //return radio_list in QList<QObject*>
	QList<QObject*> radio_list_obj;
	for (int i=0; i < _radio_list.count(); i++) {
		radio_list_obj.append(_radio_list[i]);
	}
	return radio_list_obj;
}
QList<Radio*> RadioManager::getRadioList() {
	return _radio_list;
}
void RadioManager::updateRadioManagerSignal(Radio* radio, int mIndex) {
	QString name = radio->getName();
	double frequency = radio->getFrequency();
	QString location = radio->getLocation();
	QString port_mip = radio->getPortMIP();
	double downtime = radio->getDowntime();
	int port = radio->getPort();
	QString desc = radio->getDesc();
	emit updateRadioManager(
            name, frequency, location, port_mip, downtime, port, desc, 
            radio->isOnline(),
            radio->isTx(),
            radio->isRx(),
            radio->isSQ(),
            radio->getVolume(),
            mIndex
    );
}
bool RadioManager::isOk() {
	return _flag;
}
