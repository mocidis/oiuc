#include "ctocpp.h"
#include "pstn.h"
#include "oiuc.h"
#include "radio.h"
#include "radio_manager.h"
#include "oiuc_manager.h"
#include <QtCore>
#include <QString>
#define MAX_URI_LENGTH 100
void on_reg_start_impl(int account_id) {
	printf("Acc id:: %d\n", account_id); 
}

void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason){
	ics_t *data;
	data = (ics_t *)pjsua_acc_get_user_data(account_id);
    arbiter_request_t req;
    req.msg_id = ABT_UP;
    strncpy(req.abt_up.username, data->acfg.cred_info[0].username.ptr, sizeof(req.abt_up.username));
    strncpy(req.abt_up.type, "OIU", sizeof(req.abt_up.type));
    strncpy(req.abt_up.des, "AK-47", sizeof(req.abt_up.des));
   
	PSTN *pstn = PSTN::getPSTN();
	app_data_t *app_data;
	app_data = pstn->getAppData();
	if( strcmp(is_registration, "No") == 0 ) {
        req.abt_up.is_online = 0;
		pstn->setLoggedIn(0);
		qDebug() << "offline";
	} else {
        req.abt_up.is_online = 1;
		pstn->setLoggedIn(1);
		qDebug() << "online";
	}
    send_to_arbiter(&app_data->aclient, &req);
}

void on_incoming_call_impl(int account_id, int call_id, char *remote_contact, char *local_contact) {
	QString msg = QString::fromUtf8(remote_contact);
	//msg = "incoming call from: " + msg;
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg);
}

void on_call_state_impl(int call_id, char *st_text) {
	QString msg = QString::fromUtf8(st_text);
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg);
}

void on_call_transfer_impl(int call_id, int st_code, char *st_text) {
	QString msg = QString::fromUtf8(st_text);
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg);
}

void on_call_media_state_impl(int call_id, int st_code) {
	printf("Call id: %d\n", call_id);
	printf("Status: %d\n", st_code);
}
int send_to_arbiter(arbiter_client_t *uclient, arbiter_request_t *req) {
	return arbiter_client_send(uclient, req);
}
void on_open_socket(oiu_server_t *oserver) {
    oiu_server_join(oserver, "239.0.0.1");
}
void on_request(oiu_server_t *oserver, oiu_request_t *req) {
    struct tm tm;
    time_t timer, timestamp;
    double downtime;
	int msg_id = req->msg_id;
	QString type = "unknown"; //default initial
	QString name = "unknown";
	QString status="Offline";
	QString ports_status = "";
	QString desc = "";
	QStringList list_radio_str;
	int port=0;
	OIUC *oiuc;
	OIUCManager *oiuc_manager = OIUCManager::getOIUCManager();
	RadioManager *radio_manager = RadioManager::getRadioManager();
    switch(req->msg_id) {
        case OIUC_GB:
			msg_id = req->msg_id;
			type = QString::fromLatin1(req->oiuc_gb.type);
			if ( type == "OIUC" ) {
				if (!oiuc_manager->isOk()) {
					break;
				}
				name = QString::fromLatin1(req->oiuc_gb.id);
				if (req->oiuc_gb.is_online == 1)
					status = "Online";
				else {
					time(&timer);
					tm = *localtime(&timer);
					strptime(req->oiuc_gb.timestamp, "%H:%M:%S", &tm);
					timestamp = mktime(&tm);
					downtime = difftime(timer, timestamp); //type of double
					//need emit signal if downtime detected
				}
				desc = QString::fromLatin1(req->oiuc_gb.des);
				oiuc = new OIUC(msg_id, type , name , status, desc);
				oiuc_manager->addOIUC(oiuc);
			} else if (type == "RIUC" ) {
				if (!radio_manager->isOk()) {
					break;
				}
				ports_status = QString::fromLatin1(req->oiuc_gb.ports_status);
				list_radio_str = ports_status.split(", ");
				for (int i=0; i<list_radio_str.count(); i++) {
					QStringList temp = list_radio_str[i].split("-");
					if (temp[1] == "1") {
						name = QString::fromLatin1(req->oiuc_gb.id);
						name = name + "_" + QString::number(i+1);
						port = i+1;
						if (req->oiuc_gb.is_online == 1)
							status = "Online";
						else {
							time(&timer);
							tm = *localtime(&timer);
							strptime(req->oiuc_gb.timestamp, "%H:%M:%S", &tm);
							timestamp = mktime(&tm);
							downtime = difftime(timer, timestamp); //type of double
							//need emit signal if downtime detected
						}
						double freq = req->oiuc_gb.frequence;
						QString loc = QString::fromLatin1(req->oiuc_gb.location);
						QString port_mip = QString::fromLatin1(req->oiuc_gb.ip); // need to change port_mip 
						int avaiable=0;
						if (temp[2] == "1") {
							avaiable = 1;
						}
						desc = QString::fromLatin1(req->oiuc_gb.des);
						Radio *radio = new Radio(name, status, freq, loc, port_mip, avaiable, port, desc);
						radio_manager->addRadio(radio);
					}
					name = "";
				}
			}
            break;
        default:
            fprintf(stderr, "Unknown message type. Protocol failure\n");
            exit(-1);
    }
}

