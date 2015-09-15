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
	ics_init(&app_data.ics_data);

	ics_set_reg_start_callback(&on_reg_start_impl); //cc
	ics_set_reg_state_callback(&on_reg_state_impl);
	ics_set_incoming_call_callback(&on_incoming_call_impl);
	ics_set_call_state_callback(&on_call_state_impl);
	ics_set_call_transfer_callback(&on_call_transfer_impl);
	ics_set_call_media_state_callback(&on_call_media_state_impl); //cc

	//SEND
	char send_to[] = "udp:239.0.0.1:1234";
	char listen_on[] = "udp:0.0.0.0:4321";
	arbiter_client_open(&app_data.aclient, send_to);

	ics_start(&app_data.ics_data);
	ics_connect(&app_data.ics_data, 1111);

	//Arbiter path
    // LISTEN
    app_data.oserver.on_request_f = &on_request;
    app_data.oserver.on_open_socket_f = &on_open_socket;
    oiu_server_init(&app_data.oserver, listen_on);
    oiu_server_start(&app_data.oserver);

    //End Arbiter path

	ics_add_account(&app_data.ics_data, "192.168.2.30", "ntt", "1234");

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
	ics_make_call(&app_data.ics_data, c_uri);
}
void PSTN::pstnHangupCall (QString number) {
	ics_hangup_call(&app_data.ics_data, 1);
}
void PSTN::pstnHangupAllCall (QString number) {
	ics_hangup_call(&app_data.ics_data, 1);
}
void PSTN::pstnConferenceCall (QString number) {

}
void PSTN::pstnAnswerCall (QString number) { 
	ics_answer_call(&app_data.ics_data);
}
void PSTN::pstnTransferCall (QString number) {
	ics_transfer_call(&app_data.ics_data, 1, 2);
}

void PSTN::runCallingState(QString msg) {
	emit callingState(msg);
}
app_data_t PSTN::getAppData() {
	return app_data;
}
