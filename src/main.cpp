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
#include "group_manager.h"
int main (int argc, char* argv[]) {
	QApplication app(argc, argv);
	QDeclarativeView view;
	PSTN *pstn = PSTN::getPSTN();
	view.rootContext()->setContextProperty("pstn", pstn);// setup connection between qml and cpp

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
	view.rootContext()->setContextProperty("grpManager", grp_manager);// setup connection between qml and cpp

	view.rootContext()->setContextProperty("modelRadio", QVariant::fromValue(radio_list_obj));
	view.rootContext()->setContextProperty("modelGroup",QVariant::fromValue(group_list_obj));
	view.setSource(QUrl::fromLocalFile("qml/main.qml"));
	grp_manager->setView(&view);
	view.show();
	//Radio *r = new Radio();
	//radio_list_obj.append(r);
	//view.rootContext()->setContextProperty("modelRadio", QVariant::fromValue(radio_list_obj));
	return app.exec();
}
