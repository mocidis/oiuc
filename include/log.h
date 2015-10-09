#ifndef LOG_H
#define LOG_H
#include <QtCore>
#include <QDeclarativeItem>
#include <QtSql>
#include <QDateTime>
class Log;
class Log : public QObject {
	Q_OBJECT
public:
	void logs(QString msg);
	static Log* getLog();
    static int count;
	void setFilename(QString _filename);
	Q_INVOKABLE QString getFilename();
signals:
	void writeLog(QString msg);
private:
	Log();
	static Log* log;
	QString filename;
};
void writeLog(QString msg);
#endif
