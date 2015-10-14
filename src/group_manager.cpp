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
GroupManager* GroupManager::getGroupManager() {
	//call getGroupManager(radio_manager) first
	return _grp_manager;
}
GroupManager::GroupManager(RadioManager *radio_manager) {
	_radio_manager = radio_manager;
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
	appendToDatabase(_group_list.last(), "databases/radio.db", 0);
	updateGroupManagerSignal(grp);
}
void GroupManager::addGroup (QString radio, QString grp_name, QString desc) {
	QStringList list = radio.split(", ");
	Group *grp = new Group(grp_name, radio, "online", desc);
	_group_list.append(grp);
	QList<Radio*> radio_list = _radio_manager->getRadioList();

	determineRadioListLastGroup(_group_list, radio_list);
	appendToDatabase(_group_list.last(), "databases/radio.db", 0);
	updateGroupManagerSignal(grp);
}
void GroupManager::deleteGroup(QString grp_name) {
	for (int i=0;i<_group_list.count();i++) {
		if (_group_list[i]->getName() == grp_name) {
			_group_list.removeAt(i);
		}
	}
	deleteFromDatabase(grp_name, "databases/radio.db");
}
void GroupManager::deleteGroup(int idx) {
    QString grpName = _group_list[idx]->getName();
    _group_list.removeAt(idx);
    emit groupDeleted(idx);
    deleteFromDatabase(grpName, "databases/radio.db");
}
void GroupManager::loadGrpFromDatabase() {
	_group_list = getBackendGroupList("databases/radio.db");	
	determineRadioListForGroup(_group_list, _radio_manager->getRadioList());
	for (int i=0; i<_group_list.count();i++) {
		updateGroupManagerSignal(_group_list[i]);
	}
}
/*****************Get functions******************/
QList<QObject*> GroupManager::getGroupModel() {
	QList<QObject*> group_list_obj;
	for (int i=0; i<_group_list.count(); i++) {
		group_list_obj.append(_group_list[i]);
	}
	return group_list_obj;
}
QList<Group*> GroupManager::getGroupList() {
	return _group_list;
}
void GroupManager::updateGroupManagerSignal(Group* group) {
	QString name = group->getName();
	QString desc = group->getDesc();
	int n = group->getRadioList().count();
	int m = _radio_manager->getRadioList().count();
	QList<Radio*> N = group->getRadioList();
	QList<Radio*> M = _radio_manager->getRadioList();
	QList<int> itemIdx;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			if (N[i]->getName() == M[j]->getName()) {
				itemIdx.append(j);
				writeLog("new group append");
				break;
			}
		}
	}
	int currentIdx = _group_list.indexOf(group);
	emit groupAdded(currentIdx, name, desc, itemIdx);
}
