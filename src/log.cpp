#include "log.h"
Log* Log::log = 0;
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

void writeLog(QString msg) {
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
