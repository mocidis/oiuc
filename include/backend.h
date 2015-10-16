#ifndef BACKEND_H
#define BACKEND_H
#include <QtSql>
#include <QtCore>
#include <QObject>
#include "radio.h"
#include "group.h"
#include "oiuc.h"
#include "log.h"
#include "oiuc-config.h"
QList<Radio*> getBackendRadioList (QString backend_location);
QList<OIUC*> getBackendOIUCList (QString backend_location);
QList<Group*> getBackendGroupList (QString backend_location);
void determineRadioListForGroup (QList<Group*> group, QList<Radio*> radio);
void determineRadioListLastGroup (QList<Group*> group, QList<Radio*> radio);
void writeToDatabase (QList<Group*> group, QString backend_location);
void deleteFromDatabase (QString grp_name, QString backend_location);
void appendToDatabase ( Radio *radio, QString backend_location, int dtype);
void appendToDatabase ( Group *group, QString backend_location, int dtype);
void appendToDatabase (OIUC* oiuc, QString backend_location, int dtype);
void loadGeneralConfig(OIUCConfig *oiuc_config, QString backend_location);
#endif
