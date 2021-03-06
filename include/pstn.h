#ifndef __PSTN_H__
#define __PSTN_H__
#include <QDeclarativeView>
#include <QDeclarativeItem>
#include <QDebug>
#include <QString>
#include "ctocpp.h"
#include "backend.h"
#include "oiuc-config.h"
extern "C"
{
#include "ics-command.h"
#include "ics-common.h"
#include "ics.h"
#include "ics-event.h"
#include <unistd.h>
#include <pjsua-lib/pjsua.h>
}
class PSTN;
class PSTN : public QDeclarativeItem {
	Q_OBJECT
public:
	void debug();
	static PSTN* getPSTN();
    void signalLoginStart();
	void runCallingState(QString msg, int st_code);
	app_data_t *getAppData();
	Q_INVOKABLE void pstnCall (QString number);
	Q_INVOKABLE void pstnHangupCall ();
	Q_INVOKABLE void pstnHangupAllCall ();
	Q_INVOKABLE void pstnConferenceCall ();
	Q_INVOKABLE void pstnAnswerCall ();
	Q_INVOKABLE void pstnTransferCall ();
	Q_INVOKABLE void pstnHoldCall ();
	Q_INVOKABLE void pstnReleaseHoldCall ();
	void pstnPrepare();
	Q_INVOKABLE void pstnStart(QString username, QString password);
	Q_INVOKABLE void pstnStop();
	void pstnStartAServer();
	void pstnStartOServer();
	void setLoggedIn(int flag, char *reason);
	Q_INVOKABLE bool isLoggedIn();
	Q_INVOKABLE QString getLastDialNumber();
signals:
	void callingState(QString msg, int st_code);
    void loginStart();
	void loggedInChange(QString reason);
public slots:
private:
	PSTN();
	static PSTN *singleton;
	app_data_t app_data; 
	QString current_dial_number;
	bool logged_in;
	//char send_to[30];
	//char listen_on[30];
	QString username;
	QString password;
	OIUCConfig *oiuc_config;
	//QString ip_addr;
};
#endif  //end of __PSTN_H__
