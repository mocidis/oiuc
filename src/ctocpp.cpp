#include "ctocpp.h"
#include "pstn.h"
#include <QtCore>
#include <QString>
#define MAX_URI_LENGTH 100
void on_reg_start_impl(int account_id) {
	printf("Acc id:: %d\n", account_id); 
}

void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason){
	printf("Acc id: %d\n", account_id);
	printf("Registed: %s \n", is_registration);
	printf("Status: %d(%s)\n", code, reason);
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
