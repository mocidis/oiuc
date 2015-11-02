#include "backend.h"
void loadGeneralConfig(OIUCConfig *oiuc_config, QString backend_location) {
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
		QString command = "select * from ics_config";
		QSqlQuery query = db.exec(command);
		QString asterisk_ip;
		int port_connect_asterisk=0;
		QString arbiter_ip;
		int port_sendto_arbiter=0;
		int port_oiuc_listen=0;
		QString oiuc_description; 
		double speaker_volume=0;
		double microphone_volume=0;
		QString log_dir;
		int log_max_line_per_file=0;
		int log_max_file=0;
		int log_max_line_display=0;
		while (query.next()) {
			asterisk_ip = query.value(0).toString();
			port_connect_asterisk = query.value(1).toInt();
			arbiter_ip = query.value(2).toString();
			port_sendto_arbiter = query.value(3).toInt();
			port_oiuc_listen = query.value(4).toInt();
			oiuc_description = query.value(5).toString(); 
			speaker_volume = query.value(6).toDouble();
			microphone_volume = query.value(7).toDouble();
			log_dir = query.value(8).toString();
			log_max_line_per_file = query.value(9).toInt();
			log_max_file = query.value(10).toInt();
			log_max_line_display = query.value(11).toInt();
		}
		oiuc_config->setAsteriskIP (asterisk_ip);
		oiuc_config->setPortAsterisk (port_connect_asterisk);
		oiuc_config->setArbiterIP (arbiter_ip);
		oiuc_config->setPortSendToArbiter (port_sendto_arbiter);
		oiuc_config->setPortOIUCListen (port_oiuc_listen);
		oiuc_config->setOIUCDescription (oiuc_description);
		oiuc_config->setSpeakerVolume (speaker_volume);
		oiuc_config->setMicrophoneVolume (microphone_volume);
		oiuc_config->setLogDir(log_dir);
		oiuc_config->setLogMaxLinePerFile(log_max_line_per_file);
		oiuc_config->setLogMaxFile(log_max_file);
		oiuc_config->setLogMaxLineDisplay(log_max_line_display);
			qDebug() << "run in load config---------------------" << asterisk_ip << "=" << port_connect_asterisk << arbiter_ip << port_sendto_arbiter << port_oiuc_listen << oiuc_description << speaker_volume << microphone_volume << log_max_line_per_file << log_max_file << log_max_line_display;
		writeLog("Loading Config");
	}
	QSqlDatabase::removeDatabase(backend_location);
}
