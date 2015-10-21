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
	Radio(QString name, 
        double frequency, 
        QString location, 
        QString port_mip, 
        int port, 
        QString desc,
        bool isOnline,
        bool isTx,
        bool isSQ
    );
	/*************Add and Set functions************/
	void setDowntime(double downtime);

	/************Get functions********************/
	QString getName();
	double getFrequency();
	QString getLocation();
	QString getPortMIP();
	double getDowntime();
	QString getDesc();
	int getPort();
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
	double _frequency;
	QString _location;
	QString _port_mip;
	double _downtime;
	int _port;
	QString _desc;
    bool _isOnline;
    bool _isTx;
    bool _isRx;
    bool _isSQ;
    double _volume;
};
#endif
