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
	oiuc_config = OIUCConfig::getOIUCConfig();
	current_dial_number="000"; 
	username = "youhavenoname";
	password = "youhavenopassword";
	logged_in = false;
	memset(&app_data, 0, sizeof(app_data_t));
}
void PSTN::pstnStart(QString username, QString password) {
	char user[20], passwd[20];
    if (username != NULL) {
        this->username = username;
        this->password = password;

        strncpy(user, username.toLocal8Bit().constData(), 20);
        strncpy(passwd, password.toLocal8Bit().constData(), 20);
        ics_add_account(&app_data.ics_data, oiuc_config->getAsteriskIP().toLocal8Bit().data(), user, passwd); 
    }
}
void PSTN::pstnPrepare() {
    ics_pool_init(&app_data.ics_data);
    ics_pjsua_init(&app_data.ics_data); 
    ics_init(&app_data.ics_data);

    SET_LOG_LEVEL(5);
	ics_set_default_callback(&on_reg_start_default);

	ics_set_reg_start_callback(&on_reg_start_impl); //cc
	ics_set_reg_state_callback(&on_reg_state_impl);
	ics_set_incoming_call_callback(&on_incoming_call_impl);
	ics_set_call_state_callback(&on_call_state_impl);
	ics_set_call_transfer_callback(&on_call_transfer_impl);
	ics_set_call_media_state_callback(&on_call_media_state_impl); //cc

	ics_start(&app_data.ics_data);
	//ics_connect(&app_data.ics_data, 1111);
	oiuc_config->getPortAsterisk(); // Don't need anymorea, now set default bind to any port
	ics_connect(&app_data.ics_data, oiuc_config->getPortAsterisk());
}
void PSTN::pstnStartAServer() {
	//SEND
	QByteArray send_to("udp:");
 	send_to.append(oiuc_config->getArbiterIP() + ":" + QString::number(oiuc_config->getPortSendToArbiter()));
	arbiter_client_open(&app_data.aclient, strdup(send_to.data()));
}
void PSTN::pstnStartOServer() {
    // LISTEN
    app_data.oserver.on_request_f = &on_request;
    app_data.oserver.on_open_socket_f = &on_open_socket;
	QByteArray listen_on("udp:0.0.0.0:");
	listen_on.append(QString::number(oiuc_config->getPortOIUCListen()));
    oiu_server_init(&app_data.oserver, strdup(listen_on.data()));
    oiu_server_start(&app_data.oserver);
}
void PSTN::pstnCall (QString number) {
	current_dial_number = number;
	number="sip:" + number + "@" + oiuc_config->getAsteriskIP();
	char *c_uri = number.toLatin1().data();
	ics_make_call(&app_data.ics_data, c_uri);
}
void PSTN::pstnHangupCall () {
	ics_hangup_call(&app_data.ics_data, 1);
}
void PSTN::pstnHangupAllCall () {
	ics_hangup_call(&app_data.ics_data, 1);
}
void PSTN::pstnConferenceCall () {
    // TODO
}
void PSTN::pstnAnswerCall () { 
	ics_answer_call(&app_data.ics_data);
}
void PSTN::pstnTransferCall () {
	ics_transfer_call(&app_data.ics_data, 1, 2);
}
void PSTN::pstnHoldCall () {
	ics_hold_call(&app_data.ics_data);
}
void PSTN::pstnReleaseHoldCall () {
	ics_release_hold(&app_data.ics_data);
}
void PSTN::signalLoginStart() {
    qDebug() << "---- emit onLogInStart signal ----";
    emit loginStart();
}

void PSTN::runCallingState(QString msg, int st_code) {
	emit callingState(msg, st_code);
}
app_data_t *PSTN::getAppData() {
	return &app_data;
}
QString PSTN::getLastDialNumber() {
	return current_dial_number;
}
void PSTN::setLoggedIn(int flag, char *reason) {
	logged_in = (flag == 1);
	emit loggedInChange(QString::fromLocal8Bit(reason, -1));
}
bool PSTN::isLoggedIn() {
	return logged_in;
}
void PSTN::pstnStop() {
    ics_set_registration(&app_data.ics_data, 0);
    app_data.oserver.is_online = 0;
	//setLoggedIn(0);
	//destroy PSTN here
	//
}
