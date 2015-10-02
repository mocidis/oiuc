#ifndef OIUC_MANAGER_H
#define OIUC_MANAGER_H

#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>

#include "oiuc.h"
#include "log.h"
class OIUCManager;
class OIUCManager : public QObject {
	Q_OBJECT
public:	
	static OIUCManager *getOIUCManager();
	/*****************Add and Set functions******************/
	void addOIUC (OIUC *oiuc);
	void deleteOIUC (OIUC *oiuc);
	/*****************Get functions******************/
	QList<QObject*> getModelOIUC(); //return oiuc_list in QList<QObject*>
	void updateOIUCManagerSignal (OIUC *oiuc);
signals: 
	void updateOIUCManager (QString type, QString name, QString status, QString downtime);
private:
	/*****************Constructor*******************/
	OIUCManager (QList<OIUC*> oiuc_list);
	OIUCManager ();

	/*****************Attribute********************/
	QList<OIUC*> _oiuc_list;
	static OIUCManager* _oiuc_manager;
};

#endif
