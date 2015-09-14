#include "pstn.h"
PSTN* PSTN::singleton=0;
PSTN* PSTN:: getPSTN() {
	if (!singleton) {
		singleton = new PSTN();
		return singleton;
	} else {
		return singleton;
	}	
}
PSTN::PSTN() {
	current_dial_number="0000000"; //default 7 zero number
	last_dial_number=current_dial_number;
	ics_init(&app_data); //cc

	ics_set_reg_start_callback(&on_reg_start_impl); //cc
	ics_set_reg_state_callback(&on_reg_state_impl);
	ics_set_incoming_call_callback(&on_incoming_call_impl);
	ics_set_call_state_callback(&on_call_state_impl);
	ics_set_call_transfer_callback(&on_call_transfer_impl);
	ics_set_call_media_state_callback(&on_call_media_state_impl); //cc

	ics_start(&app_data); //cc*/
	ics_connect(&app_data, 12345);
	ics_add_account(&app_data, "192.168.2.30", "ntt", "1234");

}
void PSTN::setPSTNNumberSlot(QString value) {
	current_dial_number=value;
	last_dial_number=current_dial_number;
}
void PSTN::setLastPSTNNumberSlot(QString value) {
	last_dial_number=value;
}
void PSTN::pstnCall (QString number) {
	number="sip:" + number + "@192.168.2.30";
	char *c_uri = number.toLatin1().data();
	ics_make_call(&app_data, c_uri);
}
void PSTN::pstnHangupCall (QString number) {
	ics_hangup_call(&app_data, 1);
}
void PSTN::pstnHangupAllCall (QString number) {
	ics_hangup_call(&app_data, 1);
}
void PSTN::pstnConferenceCall (QString number) {

}
void PSTN::pstnAnswerCall (QString number) { 
	ics_answer_call(&app_data);
}
void PSTN::pstnTransferCall (QString number) {
	ics_transfer_call(&app_data, 1, 2);
}

void PSTN::runCallingState(QString msg) {
	emit callingState(msg);
}
