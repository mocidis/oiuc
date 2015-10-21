#include "ctocpp.h"
#include "pstn.h"
#include "oiuc.h"
#include "radio.h"
#include "radio_manager.h"
#include "oiuc_manager.h"
#include "ics-proto.h"
#include <QtCore>
#include <QString>
#define MAX_URI_LENGTH 100

void send_cmd_to_arbiter(char *radio_list, char *cmd) {
	/*writeLog("send PTT command");
	PSTN *pstn = PSTN::getPSTN();
	app_data_t *app_data;
	app_data = pstn->getAppData();
    arbiter_request_t req;
    req.msg_id = ABT_PTT;
    strncpy(req.abt_ptt.list, radio_list, sizeof(req.abt_ptt.list));
    strncpy(req.abt_ptt.cmd_ptt, cmd, sizeof(req.abt_ptt.cmd_ptt));
    send_to_arbiter(&app_data->aclient, &req);
    */
}

void on_reg_start_impl(int account_id) {
	printf("Acc id:: %d\n", account_id);
    PSTN::getPSTN()->signalLoginStart();
}
void copy_pj_str(char *dest, pj_str_t *source) {
    strncpy(dest, source->ptr, source->slen);
}

void copy_QString(char *dest, QString &source) {
    QByteArray ba = source.toLocal8Bit();
    strncpy(dest, ba.data(), ba.size());
}

void update_online_state( int online, pj_str_t *id, QString &description ) {
    arbiter_request_t req;

    app_data_t *app_data;    
    app_data = PSTN::getPSTN()->getAppData();

    req.msg_id = ABT_UP;

    req.abt_up.type = DT_OIUC;

    copy_pj_str(req.abt_up.id, id);
    copy_QString(req.abt_up.desc, description);
    strncpy(req.abt_up.conn_str, app_data->oserver.connect_str, strlen(app_data->oserver.connect_str));

    req.abt_up.is_online = online;
   
    arbiter_client_send(&app_data->aclient, &req);
}
void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason){
	app_data_t *app_data;
	ics_t *data;
	data = (ics_t *)pjsua_acc_get_user_data(account_id);

    pj_str_t *id = &(data->acfg.cred_info[0].username);
    QString &description = OIUCConfig::getOIUCConfig()->getOIUCDescription();
    int online = 0;
    if( code == 200 && strcmp(is_registration, "No") != 0 ) {
        online = 1;
	}
    PSTN *pstn = PSTN::getPSTN();
    pstn->setLoggedIn(online, reason);
    update_online_state(online, id, description);
}

void on_incoming_call_impl(int account_id, int call_id, int st_code, char *remote_contact, char *local_contact) {
	QString msg = QString::fromUtf8(remote_contact);
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg, st_code);
}

void on_call_state_impl(int call_id, int st_code, char *st_text) {
	QString msg = QString::fromUtf8(st_text);
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg, st_code);
}

void on_call_transfer_impl(int call_id, int st_code, char *st_text) {
	QString msg = QString::fromUtf8(st_text);
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg, st_code);
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
    bool isOnline = false, isTx = false, isSQ = false;

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
	int radio_port=0;
	OIUC *oiuc;
	OIUCManager *oiuc_manager = OIUCManager::getOIUCManager();
	RadioManager *radio_manager = RadioManager::getRadioManager();
    switch(req->msg_id) {
        case OIUC_GB:
			msg_id = req->msg_id;
			if ( req->oiuc_gb.type == DT_OIUC ) {
			    type = "OIUC";
				if (!oiuc_manager->isOk()) {
					break;
				}
				name = QString::fromLocal8Bit(req->oiuc_gb.id);
				if (req->oiuc_gb.is_online == 1) {
					status = "Online";
                }
				else {
					time(&timer);
					tm = *localtime(&timer);
					strptime(req->oiuc_gb.timestamp, "%H:%M:%S", &tm);
					timestamp = mktime(&tm);
					downtime = difftime(timer, timestamp); //type of double
					//need emit signal if downtime detected
				}
				desc = QString::fromLocal8Bit(req->oiuc_gb.desc);
				oiuc = new OIUC(msg_id, type , name , status, desc);
				oiuc_manager->addOIUC(oiuc);
			} else if (req->oiuc_gb.type == DT_RIUC ) {
				if (!radio_manager->isOk()) {
					break;
                }
                double freq, volume;
                QString loc, conn_str;

                name = QString::fromLocal8Bit(req->oiuc_gb.id);
                loc = QString::fromLocal8Bit(req->oiuc_gb.location);
                desc = QString::fromLocal8Bit(req->oiuc_gb.desc);
                conn_str = QString::fromLocal8Bit(req->oiuc_gb.conn_str);

                isOnline = req->oiuc_gb.is_online;
                isTx = req->oiuc_gb.is_tx;
                isSQ = req->oiuc_gb.is_sq;
                freq = req->oiuc_gb.frequence;
                radio_port = req->oiuc_gb.radio_port;
                volume = req->oiuc_gb.volume;

                Radio *radio = new Radio(name, freq, loc, conn_str, radio_port, desc, isOnline, isTx, isSQ);
                radio_manager->addRadio(radio);
			}
            break;
        default:
            fprintf(stderr, "Unknown message type. Protocol failure\n");
            exit(-1);
    }
}

