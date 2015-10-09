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
			writeLog("database is opened");
		} else {
			writeLog("database is not opened");
		}

		QSqlQuery query = db.exec("select * from ics_radio;");
		while (query.next()) {
			QString name = query.value(0).toString();
			QString status = query.value(1).toString();
			double frequency = query.value(2).toDouble(); 
			QString location = query.value(3).toString();
			QString port_mip = query.value(4).toString();
			double downtime = query.value(5).toDouble();
			int avaiable = query.value(6).toInt();	
			int port = query.value(7).toInt();
			QString desc = query.value(8).toString();
			Radio *radio = new Radio(name,status,frequency,location,port_mip,avaiable,port,desc);
			radio->setDowntime(downtime);
			list.append(radio);
		}
	}
	QSqlDatabase::removeDatabase(backend_location);
	return list;
}
QList<OIUC*> getBackendOIUCList (QString backend_location) {
	QList<OIUC*> list;
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
			writeLog("database is opened");
		} else {
			writeLog("database is not opened");
		}

		QSqlQuery query = db.exec("select * from ics_oiuc;");
		while (query.next()) {
			int msg_id = query.value(0).toInt();
			QString type = query.value(1).toString();
			QString name = query.value(2).toString();
			QString status = query.value(3).toString();
			double downtime = query.value(4).toDouble();
			QString desc = query.value(5).toString();
			OIUC *oiuc = new OIUC(msg_id, type, name, status, desc);
			oiuc->setDowntime(downtime);
			list.append(oiuc);
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
			int avaiable = query.value(3).toInt();
			QString desc = query.value(4).toString();
			Group *group = new Group(name, radio_list, status, avaiable, desc);
			list.append(group);
		}
	}
	QSqlDatabase::removeDatabase(backend_location);
	return list;
}

void determineRadioListForGroup (QList<Group*> group, QList<Radio*> radio) {
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
}
void determineRadioListLastGroup (QList<Group*> group, QList<Radio*> radio) {
	QStringList list;
	list = group.last()->getRadioListStr().split(", ");
	for (int j=0;j<list.count();j++) {
		for (int k=0;k<radio.count();k++) {
			if (list[j] == radio[k]->getName()) {
				group.last()->addRadio(radio[k]);	
			}
		}
	}
}
void appendToDatabase (Group* group, QString backend_location) {
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
		//append code go here
		QString name = group->getName();
		QString status = group->getStatus();
		QString radio_list = group->getRadioListStr();
		int avaiable = group->getAvaiable();
		QString desc = group->getDesc();
		QSqlQuery query(db);
		query.prepare("INSERT INTO ics_group (name, radio_list, status, avaiable, desc)" "VALUES (:name, :radio_list, :status, :avaiable, :desc)");
		query.bindValue(":name", name);
		query.bindValue(":radio_list", radio_list);
		query.bindValue(":status", status);
		query.bindValue(":avaiable", avaiable);
		query.bindValue(":desc", desc);
		query.exec();
	}
	QSqlDatabase::removeDatabase(backend_location);
}
void appendToDatabase (OIUC* oiuc, QString backend_location) {
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
		//append code go here
		int msg_id = oiuc->getMsgId();
		QString name = oiuc->getName();
		QString status = oiuc->getStatus();
		QString type = oiuc->getType();
		double downtime = oiuc->getDowntime();
		QString desc = oiuc->getDesc();
		QSqlQuery query(db);
		query.prepare("INSERT INTO ics_oiuc (msg_id, type, name, status, downtime, desc)" "VALUES (:msg_id, :type, :name, :status, :downtime, :desc)");
		query.bindValue(":msg_id", msg_id);
		query.bindValue(":type", type);
		query.bindValue(":name", name);
		query.bindValue(":status", status);
		query.bindValue(":downtime", downtime);
		query.bindValue(":desc", desc);
		query.exec();
	}
	QSqlDatabase::removeDatabase(backend_location);
}
void appendToDatabase (Radio *radio, QString backend_location) {
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
		QString name = radio->getName();
		QString status = radio->getStatus();
		double freq = radio->getFrequency();
		QString localtion = radio->getLocation();
		QString p_mip = radio->getPortMIP();
		double downtime = radio->getDowntime();
		QString desc = radio->getDesc();
		int port = radio->getPort();
		int avaiable = radio->getAvaiable(); 
		QSqlQuery query(db);
		query.prepare("INSERT INTO ics_radio (name, status, frequency, localtion, port_mip, downtime, avaiable, port, desc)" "VALUES (:name, :status, :freq, :localtion, :p_mip, :downtime, :avaiable, :port, :desc)");
		query.bindValue(":name", name);
		query.bindValue(":status", status);
		query.bindValue(":freq", freq);
		query.bindValue(":localtion", localtion);
		query.bindValue(":p_mip", p_mip);
		query.bindValue(":downtime", downtime);
		query.bindValue(":avaiable",avaiable);
		query.bindValue(":port", port);
		query.bindValue(":desc", desc);
		query.exec();
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
		QSqlQuery query = db.exec(command);
		writeLog(QString::number(query.numRowsAffected()) + " group was deleted");
	}
	QSqlDatabase::removeDatabase(backend_location);
}
