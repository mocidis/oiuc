#include <pjsua-lib/pjsua.h>
#include <unistd.h>
#include "ics.h"
#include "arbiter-client.h"
#include "oiu-server.h"

struct {
    ics_t ics_data;
    arbiter_client_t aclient;
    oiu_server_t oserver;
} app_data;

static void print_menu();

static void on_reg_start_impl(int account_id);
static void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason);
static void on_incoming_call_impl(int account_id, int call_id, char *remote_contact, char *local_contact);
static void on_call_state_impl(int call_id, char *st_text);
static void on_call_transfer_impl(int call_id, int st_code, char *st_text);
static void on_call_media_state_impl(int call_id, int st_code);

static void on_request(oiu_server_t *oserver, oiu_request_t *req) {
    switch(req->msg_id) {
        case REG_STATE_RESP:
            printf("REG_STATE_RESP(%d): %d(%s) \n", req->msg_id, req->reg_state_resp.code, req->reg_state_resp.msg);
            break;
        default:
            fprintf(stderr, "Unknown message type. Protocol failure\n");
            exit(-1);
    }

}

int arbiter_send(arbiter_client_t *uclient, arbiter_request_t *req) {
	return arbiter_client_send(uclient, req);
}

static void on_init_done(oiu_server_t *oserver) {
}

static void usage(char *app) {
	printf("usage: %s <request connect string> <listen connection string>\n", app);
	exit(-1);
}

int main(int argc, char *argv[]) {

	if( argc < 3 ) {
		usage(argv[0]);
	}

	//For test only
	char option[10];
	int is_running;
	int chose;
	char sip_add[50];
	//

	ics_init(&app_data.ics_data);

	ics_set_default_callback(&on_reg_start_default);

	ics_set_reg_start_callback(&on_reg_start_impl);
	ics_set_reg_state_callback(&on_reg_state_impl);
	ics_set_incoming_call_callback(&on_incoming_call_impl);
	ics_set_call_state_callback(&on_call_state_impl);
	ics_set_call_transfer_callback(&on_call_transfer_impl);
	ics_set_call_media_state_callback(&on_call_media_state_impl);

	//SEND
	arbiter_client_open(&app_data.aclient, argv[1]);

	ics_start(&app_data.ics_data);
	ics_connect(&app_data.ics_data, 1111);

	//Arbiter path
    // LISTEN
    app_data.oserver.on_request_f = &on_request;
    app_data.oserver.on_init_done_f = &on_init_done;
    oiu_server_init(&app_data.oserver, argv[2]);
    oiu_server_start(&app_data.oserver);

    //End Arbiter path

	ics_add_account(&app_data.ics_data, "192.168.2.50", "quy", "1234");

	is_running = 1;
	while(is_running) {
		if (fgets(option, sizeof(option), stdin) == NULL ) {
			puts("NULL command\n");
		}
		switch(option[0]) {
            case 'j':
                oiu_server_join(&app_data.oserver, "239.0.0.1");
                break;
            case 'k':
                oiu_server_leave(&app_data.oserver, "239.0.0.1");
                break;
			case 'm':
				printf("Chose a call:\n");
				printf("1.quy2@192.168.2.50\n");
				printf("2.quy3@192.168.2.50\n");
				printf("3.quy10@192.168.2.50\n");
				printf("4.ntt@192.168.2.50\n");
				printf("5.ntt1@191.168.2.50\n");
				printf("6. 1\n");
				if (scanf("%d",&chose) != 1){
					printf("Invalid input value\n");
				}
				switch(chose) {
					case 1:
						strcpy(sip_add, "sip:quy2@192.168.2.50");
						ics_make_call(&app_data.ics_data, sip_add);
						break;
					case 2:
						strcpy(sip_add, "sip:quy3@192.168.2.50");
						ics_make_call(&app_data.ics_data, sip_add);
						break;	
					case 3:
                        strcpy(sip_add, "sip:quy10@192.168.2.50");
                        ics_make_call(&app_data.ics_data, sip_add);
                        break;
                    case 4:
                        strcpy(sip_add, "sip:ntt@192.168.2.50");
                        ics_make_call(&app_data.ics_data, sip_add);
                        break;
                    case 5:
                        strcpy(sip_add, "sip:ntt1@192.168.2.50");
                        ics_make_call(&app_data.ics_data, sip_add);
                        break;
                    case 6:
                        strcpy(sip_add, "sip:1@192.168.2.50");
                        ics_make_call(&app_data.ics_data, sip_add);
                        break;

                    default:
                        printf("Press 'm' to make another call\n");
                        break;
				}
				break;
			case 'a':
				ics_answer_call(&app_data.ics_data);
				break;
			case 'h':
				if (option[1] == 'a')
					ics_hangup_call(&app_data.ics_data, -2);
				else
					ics_hangup_call(&app_data.ics_data, 0);
				break;
			case 'H':
				ics_hold_call(&app_data.ics_data);
				break;
			case 'R':
				ics_release_hold(&app_data.ics_data);
				break;
			case 't':
				if (option[1] == 'x') {
					ics_adjust_audio_volume(&app_data.ics_data, "t", atof(&option[3])); // Adjust mic level (Transmitter)
				}
				else
					ics_transfer_call(&app_data.ics_data, 1, 2);
				break;
			case 'c':
				ics_conference_call(&app_data.ics_data, 1);
				break;
			case 'u':
				ics_set_registration(&app_data.ics_data, 0);
				break;
			case 'r':
				if (option[1] == 'x')
					ics_adjust_audio_volume(&app_data.ics_data, "r", atof(&option[3])); // Adjust speaker levela (Recevicer)
				else
					ics_set_registration(&app_data.ics_data, 1);
				break;
			case 'q':
				is_running = 0;
				break;
			case 'l':
				ics_list_call(&app_data.ics_data);
				break;
			case 'p':
				print_menu();
				break;
			default:
				break;
		}
	}
	ics_clean(&app_data.ics_data);
	return 0;
}

static void print_menu() {
	puts("+============================+");
	puts("|       Call Commands:       |");
	puts("|                            |");
	puts("|  m  :Make new call         |");
	puts("|  a  :Answer call           |");
	puts("|  h  :Hangup call  (ha=all) |");
	puts("|  H  :Hold call             |");
	puts("|  R  :Release hold          |");
	puts("|  t  :Tranfer call          |");
	puts("|  c  :Conference call       |");
	puts("|  u  :Un-register           |");
	puts("|  r  :Re-register           |");
	puts("|----------------------------|");
	puts("|  tx level :Adjust mic      |");
	puts("|  rx level :Adjust speaker  |");
	puts("+============================+");
}

static void on_reg_start_impl(int account_id) {
	printf("Acc id:: %d\n", account_id); 
}

static void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason){
	ics_t *data;
	data = (ics_t *)pjsua_acc_get_user_data(account_id);

	printf("Acc id: %d\n", account_id);
	printf("Registed: %s \n", is_registration);
	printf("Status: %d(%s)\n", code, reason);
    
    arbiter_request_t req;
    req.msg_id = REG_STATE_MSG;
    strncpy(req.reg_state_msg.username, data->acfg.cred_info[0].username.ptr, sizeof(req.reg_state_msg.username));
    strncpy(req.reg_state_msg.type, "OIU", sizeof(req.reg_state_msg.type));
   
	if( strcmp(is_registration, "No") == 0 )
        req.reg_state_msg.code = 0;
	else
        req.reg_state_msg.code = 1;

    arbiter_send(&app_data.aclient, &req);
}

static void on_incoming_call_impl(int account_id, int call_id, char *remote_contact, char *local_contact) {
	printf("Acc id: %d\n", account_id);
	printf("Call id: %d\n", call_id);
	printf("From: %s\n", remote_contact);	
	printf("To: %s\n", local_contact);
}

static void on_call_state_impl(int call_id, char *st_text) {
	printf("Call %d state= %s\n", call_id, st_text);
}

static void on_call_transfer_impl(int call_id, int st_code, char *st_text) {
	printf("Call id: %d\n", call_id);
	printf("Status: %d(%s)\n", st_code, st_text);
}

static void on_call_media_state_impl(int call_id, int st_code) {
	printf("Call id: %d\n", call_id);
	printf("Status: %d\n", st_code);
}


