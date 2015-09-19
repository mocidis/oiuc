#include <pjsua-lib/pjsua.h>
#include <unistd.h>
#include "ics.h"
#include "arbiter-client.h"
#include "oiu-server.h"
#include "riu-client.h"

struct {
    ics_t ics_data;
    arbiter_client_t aclient;
    oiu_server_t oserver;
} app_data;

static void print_menu();

//Callback function for Asterisk
static void on_reg_start_impl(int account_id);
static void on_reg_state_impl(int account_id, char* is_registration, int code, char *reason);
static void on_incoming_call_impl(int account_id, int call_id, char *remote_contact, char *local_contact);
static void on_call_state_impl(int call_id, char *st_text);
static void on_call_transfer_impl(int call_id, int st_code, char *st_text);
static void on_call_media_state_impl(int call_id, int st_code);
//End

//Callback function for Arbiter
static void on_request(oiu_server_t *oserver, oiu_request_t *req);

static int send_to_arbiter(arbiter_client_t *uclient, arbiter_request_t *req) {
	return arbiter_client_send(uclient, req);
}

static void on_open_socket(oiu_server_t *oserver) {
    oiu_server_join(&app_data.oserver, "239.0.0.1");
}
//End

static void usage(char *app) {
	printf("usage: %s <request connect string> <listen connection string> <command connection string>\n", app);
	exit(-1);
}

int main(int argc, char *argv[]) {
/*
	if( argc < 3 ) {
		usage(argv[0]);
	}
*/
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

#if 0
	//SEND
	arbiter_client_open(&app_data.aclient, argv[1]);
    
    riu_client_open(&app_data.rclient, )

	ics_start(&app_data.ics_data);
	ics_connect(&app_data.ics_data, 1112);

	//Arbiter path
    // LISTEN
    app_data.oserver.on_request_f = &on_request;
    app_data.oserver.on_open_socket_f = &on_open_socket;

    oiu_server_init(&app_data.oserver, argv[2]);
    oiu_server_start(&app_data.oserver);

    //End Arbiter path
#endif

#if 1
    char send_a[] = "udp:127.0.0.1:4321";
    char recv[] = "udp:0.0.0.0:1234";
	//SEND
	arbiter_client_open(&app_data.aclient, send_a);
    
	ics_start(&app_data.ics_data);
	ics_connect(&app_data.ics_data, 1111);

	//Arbiter path
    // LISTEN
    app_data.oserver.on_request_f = &on_request;
    app_data.oserver.on_open_socket_f = &on_open_socket;

    oiu_server_init(&app_data.oserver, recv);
    oiu_server_start(&app_data.oserver);

    //End Arbiter path
#endif

    //For test make cmd to RIUC only
    arbiter_request_t req;
    req.msg_id = ABT_PTT;
    strncpy(req.abt_ptt.list, "RIUC1RIUC3", sizeof(req.abt_ptt.list));
	ics_add_account(&app_data.ics_data, "192.168.2.30", "111", "1234");

	is_running = 1;
	while(is_running) {
		if (fgets(option, sizeof(option), stdin) == NULL ) {
			puts("NULL command\n");
		}
		switch(option[0]) {
            case '1':
            case '2':
            case '3':
            case '4':
                strncpy(req.abt_ptt.cmd, option, sizeof(req.abt_ptt.cmd));
                send_to_arbiter(&app_data.aclient, &req);
                break;
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
    req.msg_id = ABT_UP;
    strncpy(req.abt_up.username, data->acfg.cred_info[0].username.ptr, sizeof(req.abt_up.username));
    strncpy(req.abt_up.type, "OIU", sizeof(req.abt_up.type));
   
	if( strcmp(is_registration, "No") == 0 )
        req.abt_up.is_online = 0;
	else
        req.abt_up.is_online = 1;

    send_to_arbiter(&app_data.aclient, &req);
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

static void on_request(oiu_server_t *oserver, oiu_request_t *req) {
    struct tm tm;
    time_t timer, timestamp;
    double downtime;

   switch(req->msg_id) {
        case OIUC_GB:
    
            printf("OIUC_GB(%d):  Node id: %s(%s) - Alive: %d ", req->msg_id, req->oiuc_gb.id, req->oiuc_gb.type, req->oiuc_gb.is_online);
            
            if (0 == strcmp(req->oiuc_gb.type, "RIUC")) {
                printf("- Frequence: %.f - Location: %s - Port status: %s", req->oiuc_gb.frequence, req->oiuc_gb.location, req->oiuc_gb.ports_status);
            }
    
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
        case OIUC_SQ:
            printf("OIUC_SQ(%d):  Riuc-id: %s - Port:%d - Multicast Addr: %s \n", req->msg_id, req->oiuc_sq._id, req->oiuc_sq.port, req->oiuc_sq.multicast_addr);
            break;
        default:
            fprintf(stderr, "Unknown message type. Protocol failure\n");
            exit(-1);
    }
}

