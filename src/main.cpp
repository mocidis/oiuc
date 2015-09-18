#include <QDeclarativeView>
#include <QApplication>
#include <QDeclarativeItem>
#include <QDeclarativeContext>
#include <QDebug>
#include <QVariant>
#include "pstn.h"
#include "radio.h"
#include "group.h"
#include "backend.h"
#include "ptt.h"
#include "group_manager.h"
#include "oiuc_manager.h"
#include "radio_manager.h"
int main (int argc, char* argv[]) {
	QApplication app(argc, argv);
	QDeclarativeView view;
	PSTN *pstn = PSTN::getPSTN();
	PTT *ptt = PTT::getPTT();
	view.rootContext()->setContextProperty("pstn", pstn);// setup connection between qml and cpp
	view.rootContext()->setContextProperty("ptt", ptt);// setup connection between qml and cpp

	QList<Radio*> radio_list = getBackendRadioList("databases/radio.db"); //get list of radio

	QList<QObject*> radio_list_obj;
	for (int i=0; i<radio_list.count(); i++) {
		radio_list_obj.append(radio_list[i]);
	}
	QList<Group*> group_list = getBackendGroupList("databases/radio.db");	 //get group list
	QList<QObject*> group_list_obj;
	for (int i=0; i<group_list.count(); i++) {
		group_list_obj.append(group_list[i]);
	}
	determineRadioListForGroup(group_list,radio_list);
	GroupManager *grp_manager = new GroupManager(group_list,radio_list);	
	OIUCManager *oiuc_manager = OIUCManager::getOIUCManager ();
	RadioManager *radio_manager = RadioManager::getRadioManager();

	view.rootContext()->setContextProperty("grpManager", grp_manager);// setup connection between qml and cpp
	view.rootContext()->setContextProperty("modelRadio", QVariant::fromValue(radio_list_obj));
	view.rootContext()->setContextProperty("modelGroup", QVariant::fromValue(group_list_obj));
	view.rootContext()->setContextProperty("modelOIUC", QVariant::fromValue(oiuc_manager->getModelOIUC()));
	view.setSource(QUrl::fromLocalFile("qml/main.qml"));

	grp_manager->setView(&view);
	oiuc_manager->setView(&view);
	radio_manager->setView(&view);

	view.show();
	return app.exec();
}
