#include "ctocpp.h"
#include "pstn.h"
#include <QtCore>
#include <QString>
#define MAX_URI_LENGTH 100
void on_reg_start_impl(int account_id) {
	printf("Acc id:: %d\n", account_id); 
}

void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason){
	//printf("Acc id: %d\n", account_id);
	//printf("Registed: %s \n", is_registration);
	//printf("Status: %d(%s)\n", code, reason);
	ics_t *data;
	data = (ics_t *)pjsua_acc_get_user_data(account_id);

	printf("Acc id: %d\n", account_id);
	printf("Registed: %s \n", is_registration);
	printf("Status: %d(%s)\n", code, reason);
    
    arbiter_request_t req;
    req.msg_id = ABT_UP;
    strncpy(req.abt_up.username, data->acfg.cred_info[0].username.ptr, sizeof(req.abt_up.username));
    strncpy(req.abt_up.type, "OIU", sizeof(req.abt_up.type));
   
	if( strcmp(is_registration, "No") == 0 )
        req.abt_up.code = 0;
	else
        req.abt_up.code = 1;
	PSTN *pstn = PSTN::getPSTN();
	app_data_t *app_data;
	app_data = &pstn->getAppData();
    send_to_arbiter(&app_data->aclient, &req);
}

void on_incoming_call_impl(int account_id, int call_id, char *remote_contact, char *local_contact) {
	/*printf("Acc id: %d\n", account_id);
	printf("Call id: %d\n", call_id);
	printf("From: %s\n", remote_contact);	
	printf("To: %s\n", local_contact);*/
	QString msg = QString::fromUtf8(remote_contact);
	msg = "incoming call from: " + msg;	
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg);
}

void on_call_state_impl(int call_id, char *st_text) {
	//printf("Call %d state= %s\n", call_id, st_text);
	QString msg = QString::fromUtf8(st_text);
	PSTN *dial = PSTN::getPSTN();
	dial->runCallingState(msg);
}

void on_call_transfer_impl(int call_id, int st_code, char *st_text) {
	/*printf("Call id: %d\n", call_id);
	printf("Status: %d(%s)\n", st_code, st_text);*/
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

    switch(req->msg_id) {
        case OIUC_GB:

            printf("OIUC_GB(%d):\n  Node id: %s - Alive: %d ", req->msg_id, req->oiuc_gb.id, req->oiuc_gb.is_online);

            if (req->oiuc_gb.is_online == 1)
                printf("- Online\n");
            else {
                time(&timer);
                tm = *localtime(&timer);
                strptime(req->oiuc_gb.timestamp, "%H:%M:%S", &tm);
                timestamp = mktime(&tm);
                downtime = difftime(timer, timestamp);
                printf("- Downtime: %.f second%s\n", downtime, (downtime > 1 ? "s":""));
            }
            break;
        default:
            fprintf(stderr, "Unknown message type. Protocol failure\n");
            exit(-1);
    }
}

