#include "lowmainwindow.h"
#include<QLabel>
#include"my360button.h"
#include<QHBoxLayout>
lowMainWindow::lowMainWindow(QWidget *parent) : QMainWindow(parent)
{
	setStyleSheet("QMainWindow{background:white;}");
	setWindowFlags(Qt::FramelessWindowHint);
	setMinimumSize(900, 160);
	setMaximumSize(900, 160);

	m_btn = new mainButton(":/image/safe.png", ":/image/safe_Hover.png", ":/image/safe_Leave.png", this);
	m_btn->setGeometry(30, 30, 95, 95);
	QLabel *label = new QLabel(this);
	label->setStyleSheet("background-image:url(:/image/csxf.png)");
	label->setGeometry(45, 130, 70, 20);

	m_btn1 = new mainButton(":/image/clean.png", ":/image/clean_Hover.png", ":/image/clean_Leave.png", this);
	m_btn1->setGeometry(140, 30, 95, 95);
	QLabel *label1 = new QLabel(this);
	label1->setStyleSheet("background-image:url(:/image/dnql.png)");
	label1->setGeometry(155, 130, 70, 20);

	m_btn2 = new mainButton(":/image/youhua.png", ":/image/youhua_Hover.png", ":/image/youhua_Leave.png", this);
	m_btn2->setGeometry(250, 30, 95, 95);
	QLabel *label2 = new QLabel(this);
	label2->setStyleSheet("background-image:url(:/image/yhjs.png)");
	label2->setGeometry(265, 130, 70, 20);


	m_btn3 = new main2Button(":/image/rjgj.png", "软件管家", this);
	m_btn4 = new main2Button(":/image/rgfw.png", "人工服务", this);
	m_btn5 = new main2Button(":/image/kdcsq.png", "宽带测速器", this);
	m_btn6 = new main2Button(":/image/360wd.png", "360问答", this);
	m_btn3->setFixedSize(76, 70);
	m_btn4->setFixedSize(76, 70);
	m_btn5->setFixedSize(76, 70);
	m_btn6->setFixedSize(76, 70);

	QHBoxLayout *hlay = new QHBoxLayout(this);
	hlay->addWidget(m_btn3);
	hlay->addWidget(m_btn4);
	hlay->addWidget(m_btn5);
	hlay->addWidget(m_btn6);
	hlay->setSpacing(0);
	hlay->setGeometry(QRect(525, 80, 304, 70));

	m_btn7 = new main3Button(":/image/btn_more.png", this);
	m_btn7->setGeometry(840, 92, 32, 32);
	QPushButton *m_btn8 = new QPushButton(this);
	m_btn8->setGeometry(842, 128, 32, 24);
	m_btn8->setCursor(Qt::PointingHandCursor);
	m_btn8->setStyleSheet("QPushButton{background:transparent;color:rgb(0,135,255);}");
	m_btn8->setText("更多");

	QPushButton *m_btn9 = new QPushButton(this);
	m_btn9->setGeometry(701, 30, 173, 32);
	m_btn9->setCursor(Qt::PointingHandCursor);
	m_btn9->setStyleSheet("QPushButton{background:transparent;border-image:url(:/image/win10_normal.png);}"
		"QPushButton::hover{border-image:url(:/image/win10_hover.png);}"
		"QPushButton::pressed{border-image:url(:/image/win10_pressed.png);}");


}
