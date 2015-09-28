#include "group_manager.h"
#include "backend.h"
/*****************Constructor******************/
GroupManager* GroupManager::_grp_manager = 0;
GroupManager* GroupManager::getGroupManager(RadioManager *radio_manager) {
	if (_grp_manager == NULL) {
		_grp_manager = new GroupManager(radio_manager);	
	}
	return _grp_manager;
}
GroupManager::GroupManager(RadioManager *radio_manager) {
	_radio_manager = radio_manager;
	_grp_manager = NULL;
}

/*****************Add and Set functions******************/
void GroupManager::addGroup(Group *grp) {
	_group_list.append(grp);
}

void GroupManager::addGroup (QString radio, QString grp_name) {
	QStringList list = radio.split(", ");
	Group *grp = new Group(grp_name, radio, "online");
	_group_list.append(grp);
	QList<Radio*> radio_list = _radio_manager->getRadioList();

	determineRadioListLastGroup(_group_list, radio_list);
	//appendToDatabase(_group_list, "databases/radio.db");
	QList<QObject*> group_list_obj;
	for (int i=0;i<_group_list.count();i++) {
		group_list_obj.append(_group_list[i]);
	}
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
QList<QObject*> GroupManager::getGroupModel() {
	QList<QObject*> group_list_obj;
	for (int i=0; i<_group_list.count(); i++) {
		group_list_obj.append(_group_list[i]);
	}
	return group_list_obj;
}
