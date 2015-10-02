#ifndef RADIO_MANAGER_H
#define RADIO_MANAGER_H 

#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>
#include "radio.h"
#include "log.h"
class RadioManager;
class RadioManager : public QObject {
	Q_OBJECT
public:	
	static RadioManager *getRadioManager();
	/*****************Add and Set functions******************/
	void addRadio (Radio *radio);
	void deleteRadio (Radio *radio);
	/*****************Get functions**************************/
	QList<QObject*> getModelRadio(); //return radio_list in QList<QObject*>
	QList<Radio*> getRadioList();
	void updateRadioManagerSignal(Radio* radio);
signals: 
	void updateRadioManager(QString name, QString status, double frequency, QString location, QString port_mip, QString downtime, int avaiable, int port);
private:
	/*****************Constructor*******************/
	RadioManager (QList<Radio*> radio_list);
	RadioManager ();

	/*****************Attribute********************/
	QList<Radio*> _radio_list;
	static RadioManager* _radio_manager;
};

#endif
