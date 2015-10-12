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
	file_count = 0;
	max_file = 10;
	max_line = 1000;
	max_buffer_line = 3;
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
	fileMaintenance();
	out.setDevice(&logfile);
	logfile.setFileName(filename);
	if (!logfile.open(QIODevice::WriteOnly | QIODevice::Text) ) {
		return;
	}
	int _max_line = 0;
	int _max_buffer_line = 0;
	QString filenameS="";
	while(1) {
		if (!q_log.isEmpty()) {
			out << q_log.dequeue();
			_max_buffer_line++;
			_max_line++;
		}
		if (_max_line >= max_line) {
			out.flush();
			filenameS = filename;
			filenameS += QString::number(file_count%max_file);
			logfile.copy(this->getFilename(), filenameS);
			logfile.resize(0);
			_max_line = 0;
			filenameS = "";
			file_count++;
		}
		if (_max_buffer_line >= max_buffer_line) {
			out.flush();
		}
		msleep(500);
	} 
		logfile.close();
}
void Log::fileMaintenance() {
	for (int i=0; i<max_file; i++) {
		QFile file(filename + QString::number(i));
		if (!file.exists()) {
			QFileInfo info(file);
			file_count = i;
			if (info.size() != 0) {
				QString filenameS = filename + QString::number(i);
				file.copy(filename, filenameS); 
				file_count++;
			}
			break;
		}
	}
}
void Log::flushLog() {
	qDebug() << "-----------------FLUSH LOG---------";
	out.flush();
	logfile.close();
}
/**********************************/
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
