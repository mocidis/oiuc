#ifndef RADIO_MANAGER_H
#define RADIO_MANAGER_H 

#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>
#include "radio.h"
class RadioManager;
class RadioManager : public QObject {
	Q_OBJECT
public:	
	static RadioManager *getRadioManager();
	/*****************Add and Set functions******************/
	void addRadio (Radio *radio);
	void deleteRadio (Radio *radio);
	void setView (QDeclarativeView *view);
	/*****************Get functions**************************/
	QList<QObject*> getModelRadio(); //return radio_list in QList<QObject*>
	QList<Radio*> getRadioList();

private:
	/*****************Constructor*******************/
	RadioManager (QList<Radio*> radio_list);
	RadioManager ();

	/*****************Attribute********************/
	QList<Radio*> _radio_list;
	QDeclarativeView *_view;
	static RadioManager* _radio_manager;
};

#endif
