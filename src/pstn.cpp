#include "pstn.h"
PSTN* PSTN::singleton = 0;
PSTN* PSTN:: getPSTN() {
	if (!singleton) {
		singleton = new PSTN();
		return singleton;
	} else {
		return singleton;
	}	
}
PSTN::PSTN() {
	current_dial_number="000"; 
	last_dial_number=current_dial_number;
	username = "ntt";
	password = "1234";
	logged_in = false;
	strcpy(send_to, "udp:239.0.0.1:6789");
	strcpy(listen_on, "udp:0.0.0.0:9876");
}
void PSTN::pstnStart(QString username, QString password) {
	char user[20], passwd[20];
	this->username = username;
	this->password = password;
	strncpy(user, username.toLocal8Bit().constData(), 20);
	strncpy(passwd, password.toLocal8Bit().constData(), 20);
	ics_add_account(&app_data.ics_data, "192.168.2.30", user, passwd);
}
void PSTN::pstnPrepare() {
	ics_init(&app_data.ics_data);

	ics_set_reg_start_callback(&on_reg_start_impl); //cc
	ics_set_reg_state_callback(&on_reg_state_impl);
	ics_set_incoming_call_callback(&on_incoming_call_impl);
	ics_set_call_state_callback(&on_call_state_impl);
	ics_set_call_transfer_callback(&on_call_transfer_impl);
	ics_set_call_media_state_callback(&on_call_media_state_impl); //cc

	ics_start(&app_data.ics_data);
	ics_connect(&app_data.ics_data, 1111);
}
void PSTN::pstnStartAServer() {
	//SEND
	arbiter_client_open(&app_data.aclient, send_to);
}
void PSTN::pstnStartOServer() {
    // LISTEN
    app_data.oserver.on_request_f = &on_request;
    app_data.oserver.on_open_socket_f = &on_open_socket;

    oiu_server_init(&app_data.oserver, listen_on);
    oiu_server_start(&app_data.oserver);

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
void PSTN::pstnHangupCall () {
	ics_hangup_call(&app_data.ics_data, 1);
}
void PSTN::pstnHangupAllCall () {
	ics_hangup_call(&app_data.ics_data, 1);
}
void PSTN::pstnConferenceCall (QString number) {
    // TODO
}
void PSTN::pstnAnswerCall () { 
	ics_answer_call(&app_data.ics_data);
}
void PSTN::pstnTransferCall (QString number) {
	ics_transfer_call(&app_data.ics_data, 1, 2);
}

void PSTN::runCallingState(QString msg) {
	emit callingState(msg);
}
app_data_t *PSTN::getAppData() {
	return &app_data;
}
void PSTN::setLoggedIn(int flag) {
	if (flag == 1) {
		logged_in = true;
	} else {
		logged_in = false;
	}
	emit loggedInChange(logged_in);
}
bool PSTN::isLoggedIn() {
	return logged_in;
}
void PSTN::pstnStop() {
	setLoggedIn(0);
	//destroy PSTN here
	//
}
