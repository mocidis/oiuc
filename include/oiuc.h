#ifndef OIUC_H
#define OIUC_H

#include <QtCore>
#include <QDeclarativeItem>
#include <QtSql>
class OIUC;
class OIUC : public QObject {
	Q_OBJECT
public:
	// constructor
	OIUC();
	OIUC(QString name);
	OIUC(int msg_id, QString type, QString name, QString status);

	//add and set functions
	void setDowntime(QString downtime);
	void setStatus (QString status);
	Q_INVOKABLE void setIState (int iState);
	//get functions
	Q_INVOKABLE QString getName();
	Q_INVOKABLE QString getOIUCInfo();
	Q_INVOKABLE QString getStatus();
	Q_INVOKABLE int getIState();


private:
	int _msg_id; 
	QString _type;
	QString _name; //name of oiu
	QString _status;  //1=online or 0=offline
	QString _downtime;
	int _iState;
};


#endif
