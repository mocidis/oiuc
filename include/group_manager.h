#ifndef GROUP_MANAGER_H
#define GROUP_MANAGER_H

#include "radio.h"
#include "group.h"
#include "radio_manager.h"
#include "oiuc_manager.h"
#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>

class GroupManager;
class GroupManager : public QObject {
	Q_OBJECT
public:	
	static GroupManager* getGroupManager(RadioManager *radio_manager);
	/*****************Add and Set functions******************/
	void addGroup(Group *grp);
	Q_INVOKABLE void addGroup (QString radio, QString grp_name);
	Q_INVOKABLE void deleteGroup(QString grp_name);
	void addRadio(Radio *radio);
	void setView (QDeclarativeView *view);
	/*****************Get functions******************/
	QList<QObject*>getGroupModel();
private:
	/*****************Constructor******************/
	GroupManager(RadioManager *radio_manager);
	static GroupManager* _grp_manager;

	/****************Property**********************/
	QList<Group*> _group_list;
	RadioManager *_radio_manager; //manage list of radio currently displayed in GUI
	QDeclarativeView *_view;
};

#endif
