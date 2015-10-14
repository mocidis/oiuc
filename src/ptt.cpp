#include "ptt.h"
/**************Constructor******************/
PTT* PTT::_ptt = 0;
PTT* PTT::getPTT() {
	if (_ptt == NULL) {
		_ptt = new PTT();
	}
	return _ptt;
}
PTT::PTT() {
		
}
/****************Add and Set functions***************/
void PTT::setPTT (int index, int type, int is_pressed) { //0-Radio, 1-OIUC, 2-GROUP
	if (type == 0) {
		if (is_pressed == 1) {
			RadioManager *radio_manager = RadioManager::getRadioManager();
			QList<Radio*> radio_list = radio_manager->getRadioList();
			_radio = radio_list[index];
			_oiuc = NULL;
			_grp = NULL;
			//qDebug() << "++++++++++++++++++++++" << _radio->getName();
		}
	} else if (type == 1) {
		if (is_pressed == 1) {
			OIUCManager *oiuc_manager = OIUCManager::getOIUCManager();
			QList<OIUC*> oiuc_list = oiuc_manager->getOIUCList();
			_oiuc = oiuc_list[index];
			_radio = NULL;	
			_grp = NULL;
			//qDebug() << "++++++++++++++++++++++" << _oiuc->getName();
		}
	} else if (type == 2) {
		if (is_pressed == 1) {
			GroupManager *grp_manager = GroupManager::getGroupManager();
			QList<Group*> grp_list = grp_manager->getGroupList();
			_grp = grp_list[index];
			_radio = NULL;	
			_oiuc = NULL;
			//qDebug() << "++++++++++++++++++++++" << _grp->getName();
		}
	} else {
		_radio = NULL;	
		_oiuc = NULL;
		_grp = NULL;
		//qDebug() << "Unknown type";
	}
	_type = type;
	_is_pressed = is_pressed;
}
/*void PTT::setPTT (QObject *obj, int type, int is_pressed) { //1-Radio, 2-OIUC, 3-GROUP
	if (type == 0) {
		_radio = qobject_cast<Radio *>(obj);
		_oiuc = NULL;
		_grp = NULL;
		//qDebug() << _radio->getRadioInfo();
	} else if (type == 1) {
		_oiuc = qobject_cast<OIUC *>(obj);
		_radio = NULL;	
		_grp = NULL;
		//qDebug() << _oiuc->getOIUCInfo();
	} else if (type == 2) {
		_grp = qobject_cast<Group *>(obj);
		_radio = NULL;	
		_oiuc = NULL;
		qDebug() << _grp->getName();
	} else {
		_radio = NULL;	
		_oiuc = NULL;
		_grp = NULL;
		qDebug() << "Unknown type";
	}
	_type = type;
	_is_pressed = is_pressed;
}
*/
void PTT::setIsPressedPTT(int is_pressed) {
	_is_pressed = is_pressed;
}

void PTT::setTypePTT(int type) {
	_type = type;
}
