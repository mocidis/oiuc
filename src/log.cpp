#include "log.h"
QQueue <QString> q_log;
Log* Log::log = NULL;
Log* Log::getLog() {
	if (log == NULL) {
		log = new Log();
	}
	return log;
}
Log::Log() {
}
void Log::logs(QString msg) {
	emit writeLog(msg);
	//write to file later
}
void Log::setFilename(QString _filename) {
	filename = _filename;
}

QString Log::getFilename() {
	return filename;
}

void Log::run() {
	QFile file(log->getFilename()); 
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append) ) {
		return;
	}
	QTextStream out(&file);
	while(1) {
		if (!q_log.isEmpty()) {
			out << q_log.dequeue();
			//out.flush();
	//		qDebug() << "Queue is not empty";
		} 
        //else {
	//		qDebug() << "Queue is empty";
	//	}
		msleep(500);
	}
	file.close();
}
/**********************************/
/*void writeLog(QString msg) {
	Log *log = Log::getLog();
	log->logs(msg);
	QFile file(log->getFilename()); 
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append) ) {
		return;
	}
	QDateTime currentDate = QDateTime::currentDateTime();
	QTextStream out(&file);
	out << "\n" << "[ " << currentDate.toString("dd/MM/yy -- hh:mm:ss") << " ]" << msg;
	out.flush();
	file.close();
}
*/
void writeLog(QString msg) {
	Log *log = Log::getLog();
	log->logs(msg);
	QDateTime currentDate = QDateTime::currentDateTime();
	QString time = currentDate.toString("dd/MM/yy -- hh:mm:ss");
	QString line = "\n [ ";
	line.append(time);
	line =	line + " ]" + msg;
	q_log.enqueue(line);
}
