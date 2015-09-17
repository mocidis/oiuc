#ifndef PTT_H
#define PTT_H
#include <QtCore>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QObject>
#include "radio.h"
#include "group.h"
#include "oiuc.h"
class PTT;
class PTT : public QDeclarativeItem{
	Q_OBJECT
public:
	static PTT* getPTT();
	Q_INVOKABLE void setPTT (QObject *oiuc, int type, int is_pressed);
	Q_INVOKABLE void setIsPressedPTT (int is_pressed);
	Q_INVOKABLE void setTypePTT (int type);
private:
	PTT();
	OIUC *_oiuc;
	Group *_grp;
	Radio *_radio;
	static PTT *_ptt;
	int _is_pressed;  //0 - not pressed, 1 - pressed
	int _type; //0 - radio, 1 - oiuc, 2 - group
signals:
public slots:

};
#endif
