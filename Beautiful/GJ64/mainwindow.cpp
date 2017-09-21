#include "mainwindow.h"
#include"lowmainwindow.h"
#include<upmainwindow.h>
#include"mainwindowswidup.h"
#include"mainwindowswidlow.h"
#include"QMessageBox"
#include"QPushButton"
#include"csxfwidget.h"
#include"abstmainwidget.h"
#include"QPainterPath"
#include<qmath.h>
#include<QSystemTrayIcon>
#include"trayiconmenu.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setMinimumSize(910, 610);
	setMaximumSize(910, 610);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowIcon(QIcon(":/image/360logo.ico"));
	m_MousePressed = false;

	m_stackwid = new QStackedWidget(this);
	m_csxfwid = new Csxfwidget(m_stackwid);
	m_dnqlwid = new dnqlWidget(m_stackwid);
	m_yhjswid = new yhjsWidget(m_stackwid);

	connect(m_csxfwid->topwidget()->m_btnreturn, SIGNAL(clicked()), this, SLOT(returnanimation()));
	connect(m_dnqlwid->topwidget()->m_btnreturn, SIGNAL(clicked()), this, SLOT(returnanimation()));
	connect(m_yhjswid->topwidget()->m_btnreturn, SIGNAL(clicked()), this, SLOT(returnanimation()));

	connect(m_csxfwid->m_btnexit, SIGNAL(clicked()), this, SLOT(close()));//退出按钮
	connect(m_dnqlwid->m_btnexit, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_yhjswid->m_btnexit, SIGNAL(clicked()), this, SLOT(close()));

	connect(m_csxfwid->m_btnmini, SIGNAL(clicked()), this, SLOT(showMinimized()));//最小化按钮
	connect(m_dnqlwid->m_btnmini, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(m_yhjswid->m_btnmini, SIGNAL(clicked()), this, SLOT(showMinimized()));

	m_stackwid->addWidget(m_csxfwid);
	m_stackwid->addWidget(m_dnqlwid);
	m_stackwid->addWidget(m_yhjswid);
	m_stackwid->setGeometry(QRect(5, 5, 900, 600));
	m_stackwid->setCurrentIndex(0);

	maskmainwid = new maskmainwidget(this);
	maskmainwid->setGeometry(5, 5, 900, 600);
	connect(maskmainwid->m_upmain->m_btnexit, SIGNAL(clicked()), this, SLOT(close()));//退出按钮
	connect(maskmainwid->m_upmain->m_btnmini, SIGNAL(clicked()), this, SLOT(showMinimized()));//最小化按钮
																							  ////////////////////////////显示主界面动画
	m_maskupwincloseani = new QPropertyAnimation(maskmainwid->m_upmain, "pos");
	m_masklowwincloseani = new QPropertyAnimation(maskmainwid->m_lowmain, "pos");

	m_maskupwincloseani->setStartValue(QPoint(0, 0));
	m_maskupwincloseani->setEndValue(QPoint(0, -440));
	m_maskupwincloseani->setDuration(200);

	m_masklowwincloseani->setStartValue(QPoint(0, 440));
	m_masklowwincloseani->setEndValue(QPoint(0, 900));
	m_masklowwincloseani->setDuration(200);

	///////////////////////////用于关闭动画
	m_maskupwinshowani = new QPropertyAnimation(maskmainwid->m_upmain, "pos");
	m_masklowwinshowani = new QPropertyAnimation(maskmainwid->m_lowmain, "pos");

	m_maskupwinshowani->setStartValue(QPoint(0, -440));
	m_maskupwinshowani->setEndValue(QPoint(0, 0));
	m_maskupwinshowani->setDuration(300);

	m_masklowwinshowani->setEndValue(QPoint(0, 440));
	m_masklowwinshowani->setStartValue(QPoint(0, 900));
	m_masklowwinshowani->setDuration(300);

	connect(m_maskupwincloseani, SIGNAL(finished()), this, SLOT(slot_hideanimationfinished()));
	connect(m_masklowwincloseani, SIGNAL(finished()), this, SLOT(slot_hideanimationfinished()));


	connect(maskmainwid->m_lowmain->m_btn, SIGNAL(clicked()), this, SLOT(slot_setcurstack0()));
	connect(maskmainwid->m_lowmain->m_btn1, SIGNAL(clicked()), this, SLOT(slot_setcurstack1()));
	connect(maskmainwid->m_lowmain->m_btn2, SIGNAL(clicked()), this, SLOT(slot_setcurstack2()));

	connect(maskmainwid->m_lowmain->m_btn, SIGNAL(clicked()), this, SLOT(slot_hideanimation()));
	connect(maskmainwid->m_lowmain->m_btn1, SIGNAL(clicked()), this, SLOT(slot_hideanimation()));
	connect(maskmainwid->m_lowmain->m_btn2, SIGNAL(clicked()), this, SLOT(slot_hideanimation()));
	/////////////////////////////////////////////////////////////////////////////////////////////////系统托盘
	system_tray = new QSystemTrayIcon();
	traymenu = new trayIconMenu;
	system_tray->setContextMenu(traymenu);
	system_tray->setToolTip(QString("360安全卫士 - 安全防护中心全面开启"));
	system_tray->setIcon(QIcon(":/image/360logo.ico"));
	system_tray->show();

	connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_iconIsActived(QSystemTrayIcon::ActivationReason)));
}
void MainWindow::slot_iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		//点击托盘显示窗口
	case QSystemTrayIcon::Context:
	{
		traymenu->setGeometry(QCursor::pos().rx() - traymenu->width(), QCursor::pos().ry() - traymenu->height(), traymenu->width(), traymenu->height());//托盘菜单的位置
		break;
	}
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
	{
		showNormal();
		activateWindow();
		break;
	}
	default:
		break;
	}

}
void MainWindow::slot_hideanimationfinished()
{
	maskmainwid->hide();
}
MainWindow::~MainWindow()
{
	delete m_masklowwincloseani;
	delete m_maskupwincloseani;
	delete m_maskupwinshowani;
	delete m_masklowwinshowani;
	delete system_tray;//定要消除对象
}
void MainWindow::slot_hideanimation()//隐藏两个界面的动画
{
	m_masklowwincloseani->start();
	m_maskupwincloseani->start();
}
void MainWindow::returnanimation()
{
	maskmainwid->show();
	m_maskupwinshowani->start();
	m_masklowwinshowani->start();
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

	return QObject::eventFilter(obj, event);//反回到上一级 即重复使用
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	QRect *rc = new QRect(5, 5, 900, 150);
	if (rc->contains(this->mapFromGlobal(QCursor::pos())) == true)//如果按下的位置
	{
		if (event->button() == Qt::LeftButton)
		{

			m_WindowPos = this->pos();
			m_MousePos = event->globalPos();
			this->m_MousePressed = true;
		}
	}

}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (m_MousePressed)
	{
		this->move(m_WindowPos + (event->globalPos() - m_MousePos));
	}

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		this->m_MousePressed = false;
	}
}
void MainWindow::paintEvent(QPaintEvent *)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(9, 9, this->width() - 18, this->height() - 18);


	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));


	QColor color(0, 0, 0, 50);
	for (int i = 0; i<9; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(9 - i, 9 - i, this->width() - (9 - i) * 2, this->height() - (9 - i) * 2);
		color.setAlpha(150 - qSqrt(i) * 50);
		painter.setPen(color);
		painter.drawPath(path);
	}
}
