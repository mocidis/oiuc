#include <QDeclarativeView>
#include <QApplication>
#include <QDeclarativeItem>
#include <QDeclarativeContext>
#include <QDebug>
#include <QVariant>
#include "pstn.h"
#include "radio.h"
#include "backend.h"
#include "ptt.h"
#include "oiuc_manager.h"
#include "radio_manager.h"
#include "log.h"
#include "oiuc-config.h"
int main (int argc, char* argv[]) {
	QApplication app(argc, argv);
	QDeclarativeView view;

	//load config file

	OIUCConfig *oiuc_config = OIUCConfig::getOIUCConfig();
	loadGeneralConfig(oiuc_config, "databases/radio.db");
	
	PSTN *pstn = PSTN::getPSTN();
	pstn->pstnPrepare();
	pstn->pstnStartAServer();
	pstn->pstnStartOServer();
	

	//pstn->pstnStart("ntt", "1234");

	PTT *ptt = PTT::getPTT();
	Log *log = Log::getLog();
	log->setFilename(oiuc_config->getLogDir() + "oiuc.log");
	log->start();
	QObject::connect(&app, SIGNAL(aboutToQuit()), log, SLOT(flushLog()));
	view.rootContext()->setContextProperty("pstn", pstn);// setup connection between qml and cpp
	view.rootContext()->setContextProperty("ptt", ptt);// setup connection between qml and cpp

	OIUCManager *oiuc_manager = OIUCManager::getOIUCManager ();
	RadioManager *radio_manager = RadioManager::getRadioManager();

	view.rootContext()->setContextProperty("logModel", log->getLogModel());
	view.rootContext()->setContextProperty("radioObj", radio_manager);
	view.rootContext()->setContextProperty("oiucObj", oiuc_manager);

	view.setSource(QUrl::fromLocalFile("qml/Application.qml"));

	writeLog("Start OIUC"); //any log should declare after this line

	view.show();
	return app.exec();
}
