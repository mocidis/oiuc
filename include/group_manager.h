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
	static GroupManager* getGroupManager();
	/*****************Add and Set functions******************/
	void addGroup(Group *grp);
	Q_INVOKABLE void addGroup (QString radio, QString grp_name);
	Q_INVOKABLE void addGroup (QString radio, QString grp_name, QString desc);
	Q_INVOKABLE void deleteGroup(QString grp_name);
	Q_INVOKABLE void deleteGroup(int idx);
	void addRadio(Radio *radio);
	void loadGrpFromDatabase();

	/*****************Get functions******************/
	QList<QObject*>getGroupModel();
	QList<Group*> getGroupList();
	void updateGroupManagerSignal(Group* group);
signals: 
	void groupAdded(int currentIdx, QString name, QString desc, QList<int> itemIdx);
    void groupDeleted(int currentIdx);
private:
	/*****************Constructor******************/
	GroupManager(RadioManager *radio_manager);
	static GroupManager* _grp_manager;

	/****************Property**********************/
	QList<Group*> _group_list;
	RadioManager *_radio_manager; //manage list of radio currently displayed in GUI
};

#endif
