#include "upmainwindow.h"
#include<QLabel>
#include<QPushButton>
#include"QHBoxLayout"
#include"mainwindow.h"
#include"my360button.h"
#include"my360label.h"
UpmainWindow::UpmainWindow(QWidget *parent) : QMainWindow(parent)
{
	setMinimumSize(900, 440);
	setMaximumSize(900, 440);
	setWindowFlags(Qt::FramelessWindowHint);
	setStyleSheet("UpmainWindow{background:rgb(57,196,44);}"
		"QLabel{background:transparent;color:white;}"
		"QPushButton{background:transparent}");
	m_MousePressed = false;
	QLabel *m_logolabel = new QLabel(this);
	m_logolabel->setGeometry(10, 5, 16, 16);
	m_logolabel->setStyleSheet("border-image:url(:/image/360logo.png)");

    // 360安全卫士领航版
	QLabel *m_titlelabel = new QLabel(tr("360-Title"), this);
	m_titlelabel->setGeometry(30, 5, 105, 16);

	main3Button *m_btnupdate = new main3Button(":/image/update_btn.png", this);
	m_btnupdate->setGeometry(135, 5, 16, 16);


	m_btnmini = new main3Button(":/image/min.png", this);
	m_btnexit = new main3Button(":/image/close.png", this);
	m_btnfeedback = new main3Button(":/image/feedback.png", this);
	m_btnmenu = new main3Button(":/image/Menu.png", this);
	m_btnskin = new main3Button(":/image/Skin.png", this);

	m_btnskin->setFixedSize(29, 24);
	m_btnmini->setFixedSize(29, 24);
	m_btnexit->setFixedSize(29, 24);
	m_btnfeedback->setFixedSize(29, 24);
	m_btnmenu->setFixedSize(29, 24);

	QHBoxLayout *hlyout = new QHBoxLayout;//按顺序
	hlyout->addWidget(m_btnskin);
	hlyout->addWidget(m_btnfeedback);
	hlyout->addWidget(m_btnmenu);
	hlyout->addWidget(m_btnmini);
	hlyout->addWidget(m_btnexit);
	hlyout->setSpacing(0);
	hlyout->setGeometry(QRect(750, 0, 145, 24));

	myscoreLabel *m_labscore = new myscoreLabel(":/image/100.png", this);
	m_labscore->setGeometry(30, 85, 191, 191);


	QFont font2;
	font2.setFamily("黑体");
	font2.setPixelSize(36);


	QLabel *m_title = new QLabel("上次电脑体检良好,请继续保持！", this);
	m_title->setStyleSheet("color:white;");
	m_title->setGeometry(240, 150, 600, 40);
	m_title->setFont(font2);

	QLabel *m_title2 = new QLabel("上次体检是1分钟以前,共发现5个问题,已全部处理", this);
	m_title2->setStyleSheet("color:white;font-size:14px;");
	m_title2->setGeometry(240, 200, 400, 32);













	m_btnhead = new headButton(this);
	m_btnhead->setGeometry(840, 50, 52, 52);

	wordslineButton *m_btnword = new wordslineButton("登录360帐号", this);
	m_btnword->setGeometry(760, 70, 80, 20);

	main3Button *m_btnexamine = new main3Button(":/image/btn_examine_now.png", this);
	m_btnexamine->setGeometry(344, 285, 212, 74);



	QPushButton *m_btnsecurity = new QPushButton(this);
	m_btnsecurity->setGeometry(50, 360, 37, 37);
	m_btnsecurity->setStyleSheet("QPushButton{border-image:url(:/image/security_safe_normal.png)}"
		"QPushButton::hover{border-image:url(:/image/security_safe_hover.png)}");
	m_btnsecurity->setCursor(Qt::PointingHandCursor);

	QLabel *m_security = new QLabel("安全防护中心", this);
	m_security->setGeometry(30, 400, 100, 16);

	QLabel *label = new QLabel(this);
	label->setGeometry(120, 360, 1, 50);
	label->setStyleSheet("background:transparent;border-image:url(:/image/guardline.png);");


	QLabel *m_payfor = new QLabel("网购先陪", this);
	m_payfor->setGeometry(145, 400, 60, 16);
	QPushButton *m_btnnetpayfor = new QPushButton(this);
	m_btnnetpayfor->setGeometry(150, 360, 37, 37);
	m_btnnetpayfor->setStyleSheet("QPushButton{border-image:url(:/image/payinsure_safe_normal.png)}"
		"QPushButton::hover{border-image:url(:/image/payinsure_safe_hover.png)}");
	m_btnnetpayfor->setCursor(Qt::PointingHandCursor);


}
void UpmainWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		MainWindow *mainwin = (MainWindow *)this->parentWidget()->parentWidget();
		m_WindowPos = mainwin->pos();
		m_MousePos = event->globalPos();
		this->m_MousePressed = true;
	}
}
void UpmainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (m_MousePressed)
	{
		MainWindow *mainwin = (MainWindow *)this->parentWidget()->parentWidget();
		mainwin->move(m_WindowPos + (event->globalPos() - m_MousePos));
	}

}
void UpmainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		this->m_MousePressed = false;
	}
}
