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
#include "log.h"
int main (int argc, char* argv[]) {
	QApplication app(argc, argv);
	QDeclarativeView view;

	PSTN *pstn = PSTN::getPSTN();
	pstn->pstnPrepare();
	pstn->pstnStartAServer();
	pstn->pstnStartOServer();
	pstn->pstnStart("ntt", "1234");
	

	PTT *ptt = PTT::getPTT();
	Log *log = Log::getLog();
	log->setFilename("/tmp/oiuc.log");
	log->start();
	QObject::connect(&app, SIGNAL(aboutToQuit()), log, SLOT(flushLog()));
	view.rootContext()->setContextProperty("pstn", pstn);// setup connection between qml and cpp
	view.rootContext()->setContextProperty("ptt", ptt);// setup connection between qml and cpp

	OIUCManager *oiuc_manager = OIUCManager::getOIUCManager ();
	RadioManager *radio_manager = RadioManager::getRadioManager();
	GroupManager *grp_manager = GroupManager::getGroupManager(radio_manager);

	//view.rootContext()->setContextProperty("grpManager", grp_manager);// setup connection between qml and cpp
	//view.rootContext()->setContextProperty("modelOIUC", QVariant::fromValue(oiuc_manager->getModelOIUC()));
	view.rootContext()->setContextProperty("logModel", log->getLogModel());
	view.rootContext()->setContextProperty("radioObj", radio_manager);
	view.rootContext()->setContextProperty("oiucObj", oiuc_manager);
	view.rootContext()->setContextProperty("groupObj", grp_manager);

	view.setSource(QUrl::fromLocalFile("mockup3/Application.qml"));

	writeLog("Start OIUC"); //any log should declare after this line
	radio_manager->loadRadioFromDatabase();
	oiuc_manager->loadOIUCFromDatabase();
	grp_manager->loadGrpFromDatabase();

	view.show();
	return app.exec();
}
