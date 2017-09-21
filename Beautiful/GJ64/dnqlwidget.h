#ifndef DNQLWIDGET_H
#define DNQLWIDGET_H

#include <QObject>
#include <QWidget>
#include"abstmainwidget.h"
class dnqlWidget :public abstmainwidget
{
public:
	dnqlWidget(QWidget*parent = 0);
	void paintEvent(QPaintEvent*);
};

#endif // DNQLWIDGET_H
