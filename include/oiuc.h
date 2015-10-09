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
	OIUC(int msg_id, QString type, QString name, QString status, QString desc);

	//add and set functions
	void setDowntime(double downtime);
	void setStatus (QString status);
	//get functions
	QString getName();
	QString getStatus();
	QString getType();
	double getDowntime();
	QString getDesc();
	int getMsgId();


private:
	int _msg_id; 
	QString _type;
	QString _name; //name of oiu
	QString _status;  //1=online or 0=offline
	double _downtime;
	QString _desc;
};

#endif
