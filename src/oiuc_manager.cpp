#include "oiuc_manager.h"
#include "backend.h"
/*****************Constructor******************/
OIUCManager* OIUCManager::_oiuc_manager = 0;
OIUCManager* OIUCManager::getOIUCManager() {
	if (_oiuc_manager == NULL) {
		_oiuc_manager = new OIUCManager();
	}
	return _oiuc_manager;
}
OIUCManager::OIUCManager(QList<OIUC*> oiuc_list) {
	_flag = false;
}
OIUCManager::OIUCManager() {
	_flag = false;
}
/*****************Add and Set functions******************/
void OIUCManager::loadOIUCFromDatabase() {
	writeLog("Loading OIUC from databases");
	_oiuc_list = getBackendOIUCList("databases/radio.db");
	for (int i=0;i<_oiuc_list.count();i++) {
		updateOIUCManagerSignal(_oiuc_list[i], -1);
	}
	_flag = true;
}
void OIUCManager::addOIUC(OIUC *oiuc) {
	int flags = 0;
	int mIndex = -1;
	for (int i=0; i < _oiuc_list.count(); i++) {
		if (_oiuc_list[i]->getName() == oiuc->getName()) {
			flags = 1;
			if (_oiuc_list[i]->getStatus() != oiuc->getStatus()) {
				_oiuc_list[i]->setStatus(oiuc->getStatus());
				flags = 2;
				mIndex = i;
			}
			break;	
		}
	}
	if (flags == 0 || flags == 2) {
		if (flags == 0) {
			_oiuc_list.append(oiuc);
			appendToDatabase(oiuc, "databases/radio.db", 0);
			updateOIUCManagerSignal(oiuc, mIndex);
		} else {
			appendToDatabase(oiuc, "databases/radio.db", 1);
			updateOIUCManagerSignal(oiuc, mIndex);
		}
	}
}
void OIUCManager::deleteOIUC(OIUC *oiuc) {
	for (int i=0;i<_oiuc_list.count();i++) {
		if (_oiuc_list[i]->getName() == oiuc->getName()) {
			_oiuc_list.removeAt(i);
		}
	}
}
/*****************Get functions******************/
QList<QObject*> OIUCManager::getModelOIUC() { //return oiuc_list in QList<QObject*>
	QList<QObject*> oiuc_list_obj;
	for (int i=0; i < _oiuc_list.count(); i++) {
		oiuc_list_obj.append(_oiuc_list[i]);
	}
	return oiuc_list_obj;
}
QList<OIUC*> OIUCManager::getOIUCList() {
	return _oiuc_list;
}
void OIUCManager::updateOIUCManagerSignal (OIUC *oiuc, int mIndex) {
	QString type = oiuc->getType();
	QString name = oiuc->getName();
	QString status = oiuc->getStatus();
	double downtime = oiuc->getDowntime();
	QString desc = oiuc->getDesc();
	emit updateOIUCManager (type, name, status, downtime, desc, mIndex);
}
bool OIUCManager::isOk()  {
	return _flag;
}
