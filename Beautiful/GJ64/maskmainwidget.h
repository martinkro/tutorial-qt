#ifndef MASKMAINWIDGET_H
#define MASKMAINWIDGET_H

#include <QObject>
#include <QWidget>
#include"upmainwindow.h"
#include"lowmainwindow.h"
class maskmainwidget : public QWidget
{
	Q_OBJECT
public:
	explicit maskmainwidget(QWidget *parent = 0);
	UpmainWindow* m_upmain;
	lowMainWindow* m_lowmain;
signals:

	public slots :
};

#endif // MASKMAINWIDGET_H
