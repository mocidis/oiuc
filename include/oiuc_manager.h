#ifndef OIUC_MANAGER_H
#define OIUC_MANAGER_H

#include "oiuc.h"
#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>

class OIUCManager;
class OIUCManager : public QObject {
	Q_OBJECT
public:	
	static OIUCManager *getOIUCManager();
	/*****************Add and Set functions******************/
	void addOIUC (OIUC *oiuc);
	void deleteOIUC (OIUC *oiuc);
	void setView (QDeclarativeView *view);
	/*****************Get functions******************/
	QList<QObject*> getModelOIUC(); //return oiuc_list in QList<QObject*>

private:
	/*****************Constructor*******************/
	OIUCManager (QList<OIUC*> oiuc_list);
	OIUCManager ();

	/*****************Attribute********************/
	QList<OIUC*> _oiuc_list;
	QDeclarativeView *_view;
	static OIUCManager* _oiuc_manager;
};

#endif
