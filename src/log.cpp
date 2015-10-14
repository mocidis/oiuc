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
	logModel = new LogModel();
	logModel->roleNames();
}
void Log::logs(QString msg) {
	logModel->addLog(msg);
	if (logModel->rowCount() >= 200) {
		logModel->removeAt(logModel->rowCount() - 1);
	}
}
void Log::setFilename(QString _filename) {
	filename = _filename;
}

QString Log::getFilename() {
	return filename;
}

void Log::run() {
	logfile.setFileName(filename);
	fileMaintenance();
	if (!logfile.open(QIODevice::WriteOnly | QIODevice::Text) ) {
		return;
	}
	out.setDevice(&logfile);
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
		msleep(100);
	} 
		logfile.close();
}
void Log::fileMaintenance() {
	for (int i=0; i<max_file; i++) {
		QFile file(filename + QString::number(i));
		if (!file.exists()) {
			QFileInfo info(logfile);
			file_count = i;
			if (info.size() != 0) {
				QString filenameS = filename + QString::number(file_count);
				logfile.copy(filename, filenameS); 
				file_count++;
			}
			break;
		}
	}
}
void Log::flushLog() {
	out << "\nFILE FLUSHED";
	out.flush();
	logfile.close();
}

LogModel* Log::getLogModel() {
	return logModel;
}
/************LOGMODEL**************/
LogModel::LogModel () {
	qRegisterMetaType<QModelIndex>("QModelIndex");
	QHash<int, QByteArray> roles;
	roles[logRole] = "log";
	setRoleNames(roles);
}
void LogModel::addLog(QString msg)
{
    beginInsertRows(QModelIndex(), 0, 0);
	list.insert(0, msg);
    endInsertRows();
}

int LogModel::rowCount(const QModelIndex & parent) const {
    return list.count();
}

QVariant LogModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > list.count())
        return QVariant();

    const QString &msg = list[index.row()];
    if (role == logRole)
        return msg;
    return QVariant();
}
void LogModel::clear() {
	beginResetModel();
	list.clear();
	endResetModel();
}
void LogModel::removeAt(int index) {
	beginRemoveRows(QModelIndex(), rowCount(), rowCount());
	list.removeAt(index);
	endRemoveRows();
}

/*QHash<int, QByteArray> LogModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[logRole] = "log";
    return roles;
}*/

/**********************************/
void writeLog(QString msg) {
	Log *log = Log::getLog();
	QDateTime currentDate = QDateTime::currentDateTime();
	QString time = currentDate.toString("dd/MM/yy -- hh:mm:ss");
	QString line = "\n [ ";
	line.append(time);
	line =	line + " ] " + msg;
	log->logs(line);
	q_log.enqueue(line);
}

