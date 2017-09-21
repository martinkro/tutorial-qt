#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QStackedWidget>
#include"upmainwindow.h"
#include"lowmainwindow.h"
#include"csxfwidget.h"
#include"dnqlwidget.h"
#include"yhjswidget.h"
#include<QPropertyAnimation>
#include"maskmainwidget.h"
#include<QSystemTrayIcon>
#include"trayiconmenu.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
signals:
protected:
	bool eventFilter(QObject *, QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent*);

	bool    m_MousePressed;
	QPoint  m_MousePos;
	QPoint  m_WindowPos;
private:
	QPropertyAnimation *m_maskupwincloseani;
	QPropertyAnimation *m_masklowwincloseani;

	QPropertyAnimation *m_maskupwinshowani;
	QPropertyAnimation *m_masklowwinshowani;
	trayIconMenu *traymenu;
	QSystemTrayIcon *system_tray;
	maskmainwidget *maskmainwid;//加载最前面的两个widget
	QStackedWidget *m_stackwid;
	Csxfwidget *m_csxfwid;
	dnqlWidget *m_dnqlwid;
	yhjsWidget *m_yhjswid;
	public slots:
	void returnanimation();
	void slot_hideanimation();
	void slot_hideanimationfinished();
	void slot_setcurstack0() { m_stackwid->setCurrentIndex(0); }
	void slot_setcurstack1() { m_stackwid->setCurrentIndex(1); }
	void slot_setcurstack2() { m_stackwid->setCurrentIndex(2); }
	void slot_setcurstack3() { m_stackwid->setCurrentIndex(3); }
	private slots:
	void slot_iconIsActived(QSystemTrayIcon::ActivationReason);

};

#endif // MAINWINDOW_H
