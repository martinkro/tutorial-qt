#include "abstmainwidget.h"
#include<QVBoxLayout>
#include<QDebug>
abstmainwidget::abstmainwidget(QWidget *parent) : QWidget(parent)
{
	m_lowwid = new mainwindowswidlow(this);
	m_upwid = new mainwindowswidup(this);


	QVBoxLayout *vlyout = new QVBoxLayout(this);
	vlyout->addWidget(m_upwid);
	vlyout->addWidget(m_lowwid);
	vlyout->setSpacing(0);
	vlyout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(vlyout);


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

	QHBoxLayout *hlyout = new QHBoxLayout;//°´Ë³Ðò
	hlyout->addWidget(m_btnskin);
	hlyout->addWidget(m_btnfeedback);
	hlyout->addWidget(m_btnmenu);
	hlyout->addWidget(m_btnmini);
	hlyout->addWidget(m_btnexit);
	hlyout->setSpacing(0);
	hlyout->setGeometry(QRect(750, 0, 145, 24));


}
