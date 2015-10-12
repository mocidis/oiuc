#ifndef LOG_H
#define LOG_H
#include <QtCore>
#include <QDeclarativeItem>
#include <QtSql>
#include <QDateTime>
#include <QFile>
class Log;
class Log : public QThread {
	Q_OBJECT
public:
	void logs(QString msg);
	static Log* getLog();
	void setFilename(QString _filename);
	Q_INVOKABLE QString getFilename();
signals:
	void writeLog(QString msg);
public slots:
	void flushLog();
private:
	Log();
	void run();
	QFile logfile;
	QTextStream out;
	void fileMaintenance();
	static Log* log;
	QString filename;
	int max_file;
	int max_line;
	int max_buffer_line;
	int file_count;
};
void writeLog(QString msg);
#endif
