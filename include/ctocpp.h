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
}
//callback functions
void on_reg_start_impl (int account_id);
void on_reg_state_impl (int account_id, char* is_registration, int code, char *reason);
void on_incoming_call_impl (int account_id, int call_id, char *remote_contact, char *local_contact);
void on_call_state_impl (int call_id, char *st_text);
void on_call_transfer_impl (int call_id, int st_code, char *st_text);
void on_call_media_state_impl (int call_id, int st_code);
#endif
