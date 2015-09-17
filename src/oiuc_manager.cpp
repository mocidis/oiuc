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

}
OIUCManager::OIUCManager() {

}
/*****************Add and Set functions******************/
void OIUCManager::addOIUC(OIUC *oiuc) {
	int flags = 0;
	for (int i=0; i < _oiuc_list.count(); i++) {
		if (_oiuc_list[i]->getName() == oiuc->getName()) {
			flags = 1;
			if (_oiuc_list[i]->getStatus() != oiuc->getStatus()) {
				_oiuc_list[i]->setStatus(oiuc->getStatus());
				flags = 2;
			}
			break;	
		}
	}
	if (flags == 0 || flags == 2) {
		if (flags == 0) {
			_oiuc_list.append(oiuc);
		}
		QList<QObject*> oiuc_list_obj;
		for (int i=0;i<_oiuc_list.count();i++) {
			oiuc_list_obj.append(_oiuc_list[i]);
		}
		_view->rootContext()->setContextProperty("modelOIUC", QVariant::fromValue(oiuc_list_obj)); //update endpoint panel button
	}
}
void OIUCManager::setView(QDeclarativeView *view) {
	_view = view;
}
void OIUCManager::deleteOIUC(OIUC *oiuc) {
	for (int i=0;i<_oiuc_list.count();i++) {
		if (_oiuc_list[i]->getName() == oiuc->getName()) {
			_oiuc_list.removeAt(i);
		}
	}
	QList<QObject*> oiuc_list_obj;
	for (int i=0; i < _oiuc_list.count(); i++) {
		oiuc_list_obj.append(_oiuc_list[i]);
	}
	_view->rootContext()->setContextProperty("modelOIUC", QVariant::fromValue(oiuc_list_obj)); //update endpoint panel button
}
/*****************Get functions******************/
QList<QObject*> OIUCManager::getModelOIUC() { //return oiuc_list in QList<QObject*>
	QList<QObject*> oiuc_list_obj;
	for (int i=0; i < _oiuc_list.count(); i++) {
		oiuc_list_obj.append(_oiuc_list[i]);
	}
	return oiuc_list_obj;
}
