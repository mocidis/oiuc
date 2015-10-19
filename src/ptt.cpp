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
void PTT::setPTT (int index, int type, int is_pressed) { //0-Radio, 1-OIUC
	if (type == 0) {
		if (is_pressed == 1) {
			RadioManager *radio_manager = RadioManager::getRadioManager();
			QList<Radio*> radio_list = radio_manager->getRadioList();
			_radio = radio_list[index];
			_oiuc = NULL;
			QByteArray array_list_radio = _radio->getName().toLocal8Bit();
			char* c_str = array_list_radio.data();
			send_cmd_to_arbiter (c_str, "on");
		} else {
			QByteArray array_list_radio = _radio->getName().toLocal8Bit();
			char* c_str = array_list_radio.data();
			_radio = NULL;
			_oiuc = NULL;
			send_cmd_to_arbiter(c_str,"off");
		}
	} else if (type == 1) {
		if (is_pressed == 1) {
			OIUCManager *oiuc_manager = OIUCManager::getOIUCManager();
			QList<OIUC*> oiuc_list = oiuc_manager->getOIUCList();
			_oiuc = oiuc_list[index];
			_radio = NULL;	
			//qDebug() << "++++++++++++++++++++++" << _oiuc->getName();
		}
	} else {
		_radio = NULL;	
		_oiuc = NULL;
		//qDebug() << "Unknown type";
	}
	_type = type;
	_is_pressed = is_pressed;
}
void PTT::setIsPressedPTT(int is_pressed) {
	_is_pressed = is_pressed;
}

void PTT::setTypePTT(int type) {
	_type = type;
}
