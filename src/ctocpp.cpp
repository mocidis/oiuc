#include "ctocpp.h"
#include "pstn.h"
#include "oiuc.h"
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
   
	if( strcmp(is_registration, "No") == 0 )
        req.abt_up.is_online = 0;
	else
        req.abt_up.is_online = 1;
	PSTN *pstn = PSTN::getPSTN();
	app_data_t *app_data;
	app_data = pstn->getAppData();
    send_to_arbiter(&app_data->aclient, &req);
}

void on_incoming_call_impl(int account_id, int call_id, char *remote_contact, char *local_contact) {
	QString msg = QString::fromUtf8(remote_contact);
	msg = "incoming call from: " + msg;	
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
	OIUC *oiuc;
	OIUCManager *oiuc_manager = OIUCManager::getOIUCManager();
    switch(req->msg_id) {
        case OIUC_GB:
			msg_id = req->msg_id;
			type = QString::fromLatin1(req->oiuc_gb.type);
			if ( type == "OIUC" ) {
				name = QString::fromLatin1(req->oiuc_gb.id);
				if (req->oiuc_gb.is_online == 1)
					status = "Online";
				else {
					time(&timer);
					tm = *localtime(&timer);
					strptime(req->oiuc_gb.timestamp, "%H:%M:%S", &tm);
					timestamp = mktime(&tm);
					downtime = difftime(timer, timestamp); //type of double
				}
				oiuc = new OIUC(msg_id, type , name , status);
				oiuc_manager->addOIUC(oiuc);
			} else if (type == "RIUC" ) {
				//PARAM type char [5]
				//PARAM id char [50]
				//PARAM is_online int
				//PARAM timestamp char [20]
				//PARAM ip char [50]
				//PARAM frequence double
				//PARAM location char [50]
				//PARAM ports_status char [50]

			}
            break;
        default:
            fprintf(stderr, "Unknown message type. Protocol failure\n");
            exit(-1);
    }
}

