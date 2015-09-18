#include "group_manager.h"
#include "backend.h"
/*****************Constructor******************/
GroupManager::GroupManager(QList<Group*> group_list, QList<Radio*> radio_list) {
	for (int i=0; i < group_list.count(); i++) {
		_group_list.append(group_list[i]);
	}
	for (int i=0; i < radio_list.count(); i++) {
		_radio_list.append(radio_list[i]);
	}
}

/*****************Add and Set functions******************/
void GroupManager::addGroup(Group *grp) {
	_group_list.append(grp);
}
void GroupManager::addRadio(Radio *radio) {
	_radio_list.append(radio);
}
void GroupManager::addGroup (QString radio, QString grp_name) {
	QStringList list = radio.split(", ");
	Group *grp = new Group(grp_name, radio, "online");
	_group_list.append(grp);
	determineRadioListLastGroup(_group_list, _radio_list);
	//appendToDatabase(_group_list, "databases/radio.db");
	QList<QObject*> group_list_obj;
	for (int i=0;i<_group_list.count();i++) {
		group_list_obj.append(_group_list[i]);
	}
	qDebug() << "$$$$$$$$$$$$$$$$$$$$$$$$";
	_view->rootContext()->setContextProperty("modelGroup", QVariant::fromValue(group_list_obj)); //update endpoint panel button
}
void GroupManager::setView(QDeclarativeView *view) {
	_view = view;
}
void GroupManager::deleteGroup(QString grp_name) {
	for (int i=0;i<_group_list.count();i++) {
		if (_group_list[i]->getName() == grp_name) {
			_group_list.removeAt(i);
		}
	}
	//deleteFromDatabase(grp_name, "databases/radio.db");
	QList<QObject*> group_list_obj;
	for (int i=0;i<_group_list.count();i++) {
		group_list_obj.append(_group_list[i]);
	}
	_view->rootContext()->setContextProperty("modelGroup", QVariant::fromValue(group_list_obj)); //update endpoint panel button
}
/*****************Get functions******************/
