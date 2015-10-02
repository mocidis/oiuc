#include "backend.h"

QList<Radio*> getBackendRadioList (QString backend_location) {
	QList<Radio*> list;
	{	
		QSqlDatabase db;
		if (QSqlDatabase::contains("ics-database")) { //check duplicate sql connections.
			db = QSqlDatabase::database("ics-database");
		} else {
			db = QSqlDatabase::addDatabase("QSQLITE", "ics-database");
			db.setDatabaseName(backend_location);
			db.open();
		}
		if (db.isOpen()) {
			qDebug() << "database is opened";
		} else {
			qDebug() << "database is not opened";
		}

		QSqlQuery query = db.exec("select * from radio;");
		while (query.next()) {
			QString name = query.value(0).toString();
			QString status = query.value(1).toString();
			double frequency = query.value(2).toDouble(); 
			QString localtion = query.value(3).toString();
			QString port_mip = query.value(4).toString();
			int avaiable = query.value(5).toInt();	
			int port = query.value(6).toInt();
			Radio *radio = new Radio(name,status,frequency,localtion,port_mip,avaiable,port);
			list.append(radio);
		}
	}
	QSqlDatabase::removeDatabase(backend_location);
	return list;
}
QList<Group*> getBackendGroupList (QString backend_location) {
	QList<Group*> list;
	{
		QSqlDatabase db;
		if (QSqlDatabase::contains("ics-database")) {
			db = QSqlDatabase::database("ics-database");
		} else {
			db = QSqlDatabase::addDatabase("QSQLITE", "ics-database");
			db.setDatabaseName(backend_location);
			db.open();
		}
		if (db.isOpen()) {
			qDebug() << "database is opened";
		} else {
			qDebug() << "database is not opened";
		}

		QSqlQuery query = db.exec("select * from ics_group;");
		while (query.next()) {
			QString name = query.value(0).toString(); 
			QString radio_list = query.value(1).toString();
			QString status = query.value(2).toString();
			Group *group = new Group(name, radio_list, status);
			list.append(group);
		}
	}
	QSqlDatabase::removeDatabase(backend_location);
	return list;
}

QList<QObject*> determineRadioListForGroup (QList<Group*> group, QList<Radio*> radio) {
	for (int i=0; i<group.count(); i++) {
		QStringList list;
		list = group[i]->getRadioListStr().split(", ");
		if (list.count() >= 0) {
			for (int j=0;j<list.count();j++) {
				for (int k=0;k<radio.count();k++) {
					if (list[j] == radio[k]->getName()) {
						group[i]->addRadio(radio[k]);	
					}
				}
			}

		}
	}
	QList<QObject*> l;
	return l;
}
QList<QObject*> determineRadioListLastGroup (QList<Group*> group, QList<Radio*> radio) {
	QStringList list;
	list = group.last()->getRadioListStr().split(", ");
	for (int j=0;j<list.count();j++) {
		for (int k=0;k<radio.count();k++) {
			if (list[j] == radio[k]->getName()) {
				group.last()->addRadio(radio[k]);	
			}
		}
	}
	QList<QObject*> l;
	return l;
}
void appendToDatabase (QList<Group*> group, QString backend_location) {
	//qDebug() << "+++++++++++++++++++" << group.last()->getName();
	{
		QSqlDatabase db;
		if (QSqlDatabase::contains("ics-database")) {
			db = QSqlDatabase::database("ics-database");
		} else {
			db = QSqlDatabase::addDatabase("QSQLITE", "ics-database");
			db.setDatabaseName(backend_location);
			db.open();
		}
		if (db.isOpen()) {
			qDebug() << "database is opened";
		} else {
			qDebug() << "database is not opened";
		}
		QString name = group.last()->getName();
		QString radio_list = group.last()->getRadioListStr();
		QString status = group.last()->getGroupStatus();
		QString command = "insert into ics_group values('" + name + "\',\'" + radio_list + "\',\'" + status + "\')";
		qDebug() << "----------" << command;
		QSqlQuery query = db.exec("insert into ics_group values('" + name + "\',\'" + radio_list + "\',\'" + status + "\')");
	}
	QSqlDatabase::removeDatabase(backend_location);
}
void deleteFromDatabase (QString grp_name, QString backend_location) {
	{
		QSqlDatabase db;
		if (QSqlDatabase::contains("ics-database")) {
			db = QSqlDatabase::database("ics-database");
		} else {
			db = QSqlDatabase::addDatabase("QSQLITE", "ics-database");
			db.setDatabaseName(backend_location);
			db.open();
		}
		if (db.isOpen()) {
			qDebug() << "database is opened";
		} else {
			qDebug() << "database is not opened";
		}
		QString command = "delete from ics_group where name=\'" + grp_name + "\'";
		qDebug() << "----------" << command;
		QSqlQuery query = db.exec(command);
	}
	QSqlDatabase::removeDatabase(backend_location);
}
