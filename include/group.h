#ifndef GROUP_H
#define GROUP_H
#include "radio.h"
#include <QtCore>
#include <QDeclarativeItem>
#include <QtSql>

class Group;
class Group : public QObject {
	Q_OBJECT
public:	
	/*****************Constructor******************/
	Group();
	Group(QString name, QString radio_list_str, QString status);

	/*****************Add and Set functions******************/
	void setRadioList(QList<Radio*> radio_list);
	void addRadio(Radio *radio);
	void setStatus(QString status);
	Q_INVOKABLE void setIState(int iState);
	void setAvaiable(int avaiable);

	/*****************Get functions******************/
	QString getRadioListStr();
	QString getGroupStatus();

	//INVOKABLE METHOS
	Q_INVOKABLE QList<QObject*> getRadioList();
	Q_INVOKABLE QString getName ();
	Q_INVOKABLE int getRadioListSize();
	QString getStatus();
	Q_INVOKABLE int getIState();
	int getAvaiable();
private:
	QString _name;
	QString _status;
	QString _radio_list_str;
	QList<QObject*> _radio_list;
	int _avaiable;
	int _iState; // qml used
};

#endif
