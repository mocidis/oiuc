#ifndef CTOCPP_H
#define CTOCPP_H
#include <QtCore>
#include <QString>
extern "C"
{
#include "ics-command.h"
#include "ics-common.h"
#include "ics.h"
#include "ics-event.h"
#include <unistd.h>
#include "arbiter-client.h"
#include "arbiter.h"
#include "arbiter-server.h"
#include "oiu-client.h"
#include "oiu.h"
#include "oiu-server.h"
}
typedef struct {
    ics_t ics_data;
    arbiter_client_t aclient;
    oiu_server_t oserver;
} app_data_t;
//callback functions
void on_reg_start_impl (int account_id);
void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason);
void on_incoming_call_impl (int account_id, int call_id, char *remote_contact, char *local_contact);
void on_call_state_impl (int call_id, int st_code, char *st_text);
void on_call_transfer_impl (int call_id, int st_code, char *st_text);
void on_call_media_state_impl (int call_id, int st_code);

//Callback function for Arbiter
void on_request(oiu_server_t *oserver, oiu_request_t *req);
int send_to_arbiter(arbiter_client_t *uclient, arbiter_request_t *req);
void on_open_socket(oiu_server_t *oserver);
//End
#endif
