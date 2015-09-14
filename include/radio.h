#ifndef RADIO_H
#define RADIO_H

#include <QtCore>
#include <QDeclarativeItem>
#include <QtSql>
class Radio;
class Radio : public QObject {
	Q_OBJECT
public:
	Radio();
	Radio(QString name);
	Radio(QString name, QString status, double frequency, QString location);
	Q_INVOKABLE QString getName();
	Q_INVOKABLE QString getRadioInfo();
private:
	//QStringList radio_list;
	QString _name;
	QString _status; //(online, offline)
	//time_t double downtime; /
	double _frequency;
	QString _location;
};


#endif
