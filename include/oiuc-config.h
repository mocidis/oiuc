#ifndef OIUC_CONFIG
#define OIUC_CONFIG

#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>
#include "log.h"
class OIUCConfig;
class OIUCConfig : public QObject {
	Q_OBJECT
public:	
	static OIUCConfig *getOIUCConfig();
	/**************ADD and SET FUNCTIONS*****/
	Q_INVOKABLE void setAsteriskIP(QString value);
	Q_INVOKABLE void setPortAsterisk(int value);
	Q_INVOKABLE void setArbiterIP(QString value );
	Q_INVOKABLE void setPortSendToArbiter(int value);
	Q_INVOKABLE void setPortOIUCListen(int value);
	Q_INVOKABLE void setOIUCDescription(QString value);
	Q_INVOKABLE void setSpeakerVolume(double value);
	Q_INVOKABLE void setMicrophoneVolume(double value);
	Q_INVOKABLE void setLogDir(QString value);
	/**************GET FUNCTIONS*************/
	Q_INVOKABLE QString getAsteriskIP();
	Q_INVOKABLE int getPortAsterisk();
	Q_INVOKABLE QString getArbiterIP();
	Q_INVOKABLE int getPortSendToArbiter();
	Q_INVOKABLE int getPortOIUCListen();
	Q_INVOKABLE QString getOIUCDescription();
	Q_INVOKABLE double getSpeakerVolume();
	Q_INVOKABLE double getMicrophoneVolume();
	Q_INVOKABLE QString getLogDir();
private:
	/*****************Constructor*******************/
	OIUCConfig ();
	static OIUCConfig *_oiuc_config;
	/*****************Attribute********************/
	QString asterisk_ip;
	int port_connect_asterisk;
	QString arbiter_ip;
	int port_sendto_arbiter;
	int port_oiuc_listen;
	QString oiuc_description; 
	double speaker_volume;
	double microphone_volume;
	QString log_dir;
};

#endif
