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
	Group(QString name, QString radio_list_str, QString status, QString desc);
	Group(QString name, QString radio_list_str, QString status, int avaiable, QString desc);

	/*****************Add and Set functions******************/
	void setRadioList(QList<Radio*> radio_list);
	void addRadio(Radio *radio);
	void setStatus(QString status);
	void setAvaiable(int avaiable);
	void setDesc(QString desc);

	/*****************Get functions******************/
	QString getRadioListStr();
	QString getGroupStatus();

	//INVOKABLE METHOS
	Q_INVOKABLE QList<Radio*> getRadioList();
	Q_INVOKABLE QString getName ();
	Q_INVOKABLE int getRadioListSize();
	QString getStatus();
	int getAvaiable();
	QString getDesc();
private:
	QString _name;
	QString _status;
	QString _radio_list_str;
	QList<Radio*> _radio_list;
	int _avaiable;
	QString _desc;
};

#endif
