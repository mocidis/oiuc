#ifndef BACKEND_H
#define BACKEND_H
#include <QtSql>
#include <QtCore>
#include "log.h"
#include "oiuc-config.h"
void loadGeneralConfig(OIUCConfig *oiuc_config, QString backend_location);
#endif
