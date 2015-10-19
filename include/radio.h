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
	Radio(QString name, QString status, double frequency, QString location, QString port_mip, int avaiable, int port, QString desc);
	/*************Add and Set functions************/
	void setStatus(QString status);
	void setDowntime(double downtime);
	void setAvaiable(int avaiable);

	/************Get functions********************/
	QString getName();
	QString getStatus();
	double getFrequency();
	QString getLocation();
	QString getPortMIP();
	double getDowntime();
	QString getDesc();
	int getPort();
	int getAvaiable();
    bool isOnline();
    bool isTx();
    bool isRx();
    //bool isRxBlocked();
    bool isSQ();
    double getVolume();
    
    void setOnline(bool val);
    void setTx(bool val);
    void setRx(bool val);
    void setSQ(bool val);
    void setVolume(double val);

private:
	QString _name;
	QString _status; //(online, offline)
	double _frequency;
	QString _location;
	QString _port_mip;
	double _downtime;
	int _port;
	int _avaiable;
	QString _desc;
    bool _isOnline;
    bool _isTx;
    bool _isRx;
    bool _isSQ;
    bool _volume;
};
#endif
