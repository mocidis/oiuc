#ifndef BACKEND_H
#define BACKEND_H
#include <QtSql>
#include <QtCore>
#include <QObject>
#include "radio.h"
#include "group.h"

QList<Radio*> getBackendRadioList (QString backend_location);
QList<Group*> getBackendGroupList (QString backend_location);
QList<QObject*> determineRadioListForGroup (QList<Group*> group, QList<Radio*> radio);
QList<QObject*> determineRadioListLastGroup (QList<Group*> group, QList<Radio*> radio);
void writeToDatabase (QList<Group*> group, QString backend_location);
void deleteFromDatabase (QString grp_name, QString backend_location);
#endif
