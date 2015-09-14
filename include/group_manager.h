#ifndef GROUP_MANAGER_H
#define GROUP_MANAGER_H

#include "radio.h"
#include "group.h"
#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QtSql>

class GroupManager;
class GroupManager : public QObject {
	Q_OBJECT
public:	
	/*****************Constructor******************/
	GroupManager(QList<Group*> group_list, QList<Radio*> radio_list);

	/*****************Add and Set functions******************/
	void addGroup(Group *grp);
	Q_INVOKABLE void addGroup (QString radio, QString grp_name);
	Q_INVOKABLE void deleteGroup(QString grp_name);
	void addRadio(Radio *radio);
	void setView (QDeclarativeView *view);
	/*****************Get functions******************/
private:
	QList<Group*> _group_list;
	QList<Radio*> _radio_list;
	QDeclarativeView *_view;
};

#endif
