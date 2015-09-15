#ifndef __PSTN_H__
#define __PSTN_H__
#include <QDeclarativeView>
#include <QDeclarativeItem>
#include <QDebug>
#include <QString>
#include "ctocpp.h"
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
	app_data_t getAppData();
	Q_INVOKABLE void pstnCall (QString number);
	Q_INVOKABLE void pstnHangupCall (QString number);
	Q_INVOKABLE void pstnHangupAllCall (QString number);
	Q_INVOKABLE void pstnConferenceCall (QString number);
	Q_INVOKABLE void pstnAnswerCall (QString number);
	Q_INVOKABLE void pstnTransferCall (QString number);
signals:
	void callingState(QString msg);
public slots:
	void setPSTNNumberSlot (QString value);
	void setLastPSTNNumberSlot (QString value);
	//void pstnCallSlot (QString number);
	//void pstnHangupCallSlot (QString number);
	//void pstnHangupAllCallSlot (QString number);
	//void pstnConferenceCallSlot (QString number);
	//void pstnAnswerCallSlot (QString number);
	//void pstnTransferCallSlot (QString number);
private:
	PSTN();
	static PSTN *singleton;
	app_data_t app_data; 
	QString current_dial_number;
	QString last_dial_number;
};
#endif  //end of __PSTN_H__
