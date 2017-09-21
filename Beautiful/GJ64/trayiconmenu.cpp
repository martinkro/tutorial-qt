#include "trayiconmenu.h"
#include<QAction>
#include<QWidgetAction>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"my360button.h"
#include<QWidgetAction>
#include<QPainter>
#include<QPainterPath>
#include<qmath.h>
#include<QLabel>
trayIconMenu::trayIconMenu(QWidget*parent) :QMenu(parent)
{
	initlevel5();
	initlevel4();
	initlevel3();
	initlevel2();//
	initlevel1();//第二层
	initlevel0();//第一层
	setStyleSheet("QMenu{border:NULL;background:white;color: rgb(88,88,88);}"
		"QMenu::item{height:26px;background:white;}"
		"QMenu::item::selected{background:white;background-color:rgb(242,242,242);}");

}
void trayIconMenu::initlevel5()
{
	QWidgetAction *widaction = new QWidgetAction(this);

	level5Widget *level5wid = new level5Widget(this);

	widaction->setDefaultWidget(level5wid);
	addAction(widaction);
}
void trayIconMenu::initlevel4()
{
	QWidgetAction *widaction = new QWidgetAction(this);

	level4Widget *level4wid = new level4Widget(this);

	widaction->setDefaultWidget(level4wid);
	addAction(widaction);
}
void trayIconMenu::initlevel3()
{
	QAction *actioninfo = new QAction(QIcon(":/image/traymen/ico_switchmode.png"), "游戏,网购模式", this);
	QMenu *menuupdate = new QMenu(this);
	QAction *actionappupdate = new QAction(QIcon(":/image/traymen/ico_game_mode.png"), "进入游戏模式", this);
	QAction *actiondownloadmanger = new QAction(QIcon(":/image/traymen/ico_netpay_mode.png"), "进入网购模式", this);

	menuupdate->addAction(actionappupdate);
	menuupdate->addAction(actiondownloadmanger);
	actioninfo->setMenu(menuupdate);
	addAction(actioninfo);
}
void trayIconMenu::initlevel2()
{
	QAction *actioninfo = new QAction(QIcon(":/image/traymen/ico_update.png"), "升级", this);
	QMenu *menuupdate = new QMenu(this);
	QAction *actionappupdate = new QAction(QIcon(":/image/traymen/ico_update_item.png"), "程序升级", this);
	QAction *actiondownloadmanger = new QAction(QIcon(":/image/traymen/ico_download_mgr.png"), "360下载管理", this);

	menuupdate->addAction(actionappupdate);
	menuupdate->addAction(actiondownloadmanger);
	actioninfo->setMenu(menuupdate);
	addAction(actioninfo);
}
void trayIconMenu::initlevel1()
{
	QAction *actioninfo = new QAction(QIcon(":/image/traymen/ico_safenotify.png"), "安全通知", this);
	addAction(actioninfo);
}
void trayIconMenu::initlevel0()
{
	QWidgetAction *action = new QWidgetAction(this);
	m_widlevel0 = new QWidget(this);
	QHBoxLayout *hyout = new QHBoxLayout(m_widlevel0);//each 87*32
	main3Button *m_btnsetting = new main3Button(":/image/traymen/button_setting.png", m_widlevel0);//设置
	main3Button *m_btnfeedback = new main3Button(":/image/traymen/button_feedback.png", m_widlevel0);//建议
	main3Button *m_btnexit = new main3Button(":/image/traymen/button_exit.png", m_widlevel0);//退出


	m_btnsetting->setFixedSize(87, 32);
	m_btnfeedback->setFixedSize(87, 32);
	m_btnexit->setFixedSize(87, 32);

	hyout->addWidget(m_btnsetting);
	hyout->addWidget(m_btnfeedback);
	hyout->addWidget(m_btnexit);
	hyout->setSpacing(0);
	hyout->setContentsMargins(0, 0, 0, 0);
	m_widlevel0->setLayout(hyout);
	m_widlevel0->setMaximumWidth(261);
	m_widlevel0->setMinimumWidth(261);
	action->setDefaultWidget(m_widlevel0);
	m_widlevel0->setContentsMargins(0, 0, 0, 0);
	m_widlevel0->setStyleSheet("QWidget{border-image:url(:/image/traymen/bg_safe.png);}");
	addAction(action);
}
void trayIconMenu::paintEvent(QPaintEvent *e)
{
	QMenu::paintEvent(e);
	/* QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(9, 9, this->width()-18, this->height()-18);


	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));


	QColor color(0, 0, 0, 50);
	for(int i=0; i<9; i++)
	{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
	color.setAlpha(150 - qSqrt(i)*50);
	painter.setPen(color);
	painter.drawPath(path);
	}*/

}
////////////////////////////////////////////////////////////
level4Widget::level4Widget(QWidget *parent) :QWidget(parent)
{
	QVBoxLayout *vlayout = new QVBoxLayout;
	QVBoxLayout *vlayout1 = new QVBoxLayout;
	QHBoxLayout *hlayout = new QHBoxLayout;
	main6Button *m_btn = new main6Button(":/image/traymen/ico_360safe.png", "打开卫士", this);//以坚起为顺序
	main6Button *m_btn1 = new main6Button(":/image/traymen/ico_safecheck.png", "查杀修复", this);
	main6Button *m_btn2 = new main6Button(":/image/traymen/ico_speed.png", "优化加速", this);
	main6Button *m_btn3 = new main6Button(":/image/traymen/ico_examine.png", "电脑体检", this);
	main6Button *m_btn4 = new main6Button(":/image/traymen/ico_clean.png", "电脑清理", this);
	main6Button *m_btn5 = new main6Button(":/image/traymen/ico_softmgr.png", "软件管家", this);

	m_btn->setFixedSize(130, 92);
	m_btn1->setFixedSize(130, 92);
	m_btn2->setFixedSize(130, 92);
	m_btn3->setFixedSize(130, 92);
	m_btn4->setFixedSize(130, 92);
	m_btn5->setFixedSize(130, 92);

	vlayout->addWidget(m_btn);
	vlayout->addWidget(m_btn1);
	vlayout->addWidget(m_btn2);
	vlayout->setSpacing(1);

	vlayout1->addWidget(m_btn3);
	vlayout1->addWidget(m_btn4);
	vlayout1->addWidget(m_btn5);
	vlayout1->setSpacing(1);

	hlayout->addLayout(vlayout);
	hlayout->addLayout(vlayout1);
	hlayout->setSpacing(1);
	hlayout->setContentsMargins(0, 0, 0, 0);
	setContentsMargins(0, 0, 0, 0);
	this->setLayout(hlayout);

	setMaximumWidth(261);
	setMinimumWidth(261);

}
void level4Widget::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setPen(QColor(235, 235, 235));
	p.drawLine(QPoint(width() / 2 + 1, 0), QPoint(width() / 2, height()));
	p.drawLine(QPoint(0, height() / 3), QPoint(width(), height() / 3));
	p.drawLine(QPoint(0, height() * 2 / 3), QPoint(width(), height() * 2 / 3));
	p.drawLine(QPoint(0, height() - 1), QPoint(width(), height() - 1));
}
///////////////////////////////////////////////////////////////////////////
level5Widget::level5Widget(QWidget *parent) :QWidget(parent)
{
	setStyleSheet("border-image:url(:/image/traymen/bg_safe.png)");
	QVBoxLayout *vlayout = new QVBoxLayout;
	QHBoxLayout *hlayout = new QHBoxLayout;
	QHBoxLayout *hlayout1 = new QHBoxLayout;
	main3Button *m_btn = new main3Button(":/image/traymen/ico_protect_opened.png", this);//以坚起为顺序
	main3Button *m_btn1 = new main3Button(":/image/traymen/ico_enter_safe_center.png", this);
	m_btn->setFixedSize(133, 25);
	m_btn1->setFixedSize(28, 16);
	hlayout->addWidget(m_btn, 0, Qt::AlignLeft);
	hlayout->addWidget(m_btn1, 0, Qt::AlignLeft);
	hlayout->setSpacing(30);
	hlayout->setContentsMargins(5, 0, 0, 0);
	QLabel *label = new QLabel("360安全卫士已保护您的电脑365天", this);
	hlayout1->addWidget(label);
	hlayout1->setContentsMargins(6, 0, 0, 0);
	label->setStyleSheet("color:white");
	QFont font;
	font.setBold(true);
	label->setFont(font);

	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout);
	vlayout->setSpacing(0);
	setLayout(vlayout);

	setFixedSize(261, 70);

}
void level5Widget::paintEvent(QPaintEvent *e)
{
	QWidget::paintEvent(e);
}
