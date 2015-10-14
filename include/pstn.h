#ifndef __PSTN_H__
#define __PSTN_H__
#include <QDeclarativeView>
#include <QDeclarativeItem>
#include <QDebug>
#include <QString>
#include "ctocpp.h"
#include "backend.h"
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
	void runCallingState(QString msg);
	app_data_t *getAppData();
	Q_INVOKABLE void pstnCall (QString number);
	Q_INVOKABLE void pstnHangupCall ();
	Q_INVOKABLE void pstnHangupAllCall ();
	Q_INVOKABLE void pstnConferenceCall (QString number);
	Q_INVOKABLE void pstnAnswerCall ();
	Q_INVOKABLE void pstnTransferCall (QString number);
	void pstnPrepare();
	Q_INVOKABLE void pstnStart(QString username, QString password);
	Q_INVOKABLE void pstnStop();
	void pstnStartAServer();
	void pstnStartOServer();
	void setLoggedIn(int flag);
	Q_INVOKABLE bool isLoggedIn();
	Q_INVOKABLE QString getLastDialNumber();
signals:
	void callingState(QString msg);
	void loggedInChange(bool logged_in);
public slots:
private:
	PSTN();
	static PSTN *singleton;
	app_data_t app_data; 
	QString current_dial_number;
	bool logged_in;
	char send_to[30];
	char listen_on[30];
	QString username;
	QString password;
	QString ip_addr;
};
#endif  //end of __PSTN_H__
