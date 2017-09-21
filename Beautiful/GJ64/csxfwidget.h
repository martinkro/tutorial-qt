#ifndef CSXFWIDGET_H
#define CSXFWIDGET_H
#include"abstmainwidget.h"
#include <QObject>
#include <QWidget>
#include"my360button.h"
class Csxfwidget :public abstmainwidget
{
	Q_OBJECT
public:
	Csxfwidget(QWidget *parent = 0);
};

#endif // CSXFWIDGET_H
