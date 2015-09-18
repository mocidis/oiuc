#ifndef RADIO_H
#define RADIO_H

#include <QtCore>
#include <QDeclarativeItem>
#include <QtSql>
class Radio;
class Radio : public QObject {
	Q_OBJECT
public:
	/****************Constructor*******************/
	Radio();
	Radio(QString name);
	Radio(QString name, QString status, double frequency, QString location, QString port_mip, int avaiable);
	/*************Add and Set functions************/
	void setStatus(QString status);
	Q_INVOKABLE void setIState(int iState);
	void setDowntime(QString downtime);
	void setAvaiable(int avaiable);

	/************Get functions********************/
	Q_INVOKABLE QString getName();
	Q_INVOKABLE QString getRadioInfo();
	QString getStatus();
	Q_INVOKABLE int getIState();
	int getAvaiable();

private:
	//QStringList radio_list;
	QString _name;
	QString _status; //(online, offline)
	//QString downtime;
	double _frequency;
	QString _location;
	QString _port_mip;
	QString _downtime;
	int _avaiable;
	int _iState; // qml used
};
#endif
