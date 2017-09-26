#include "LoginTitleBar.h"

const int TITLE_BAR_HEIGHT = 20;

LoginTitleBar::LoginTitleBar(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
	
}


void LoginTitleBar::initUI()
{
	//this->setStyleSheet("border-color:black;border-width:1px;border-style:solid;");
	setFixedHeight(TITLE_BAR_HEIGHT);
	
	//////////////////////////////////////////////////////////////////////////
	// initialize top part
	
	m_labelTitle = new QLabel(tr("PP"));
	QFont font = const_cast<QFont&>(m_labelTitle->font());
	font.setBold(true);
	font.setPointSize(10);
	m_labelTitle->setFont(font);
	m_labelTitle->setObjectName("LabelTitle");

	m_buttonMinimized = new PushButton;
	m_buttonMinimized->setButtonBackground(tr(":/sysbuttons/min"));
	m_buttonMinimized->setToolTip(tr("Minimize"));

	m_buttonClose = new PushButton;
	m_buttonClose->setButtonBackground(tr(":/sysbuttons/close"));
	m_buttonClose->setToolTip(tr("Close"));

	m_layoutMain = new QHBoxLayout;
	m_layoutMain->addWidget(m_labelTitle, 0, Qt::AlignVCenter);
	m_layoutMain->addStretch();
	m_layoutMain->addWidget(m_buttonMinimized, 0, Qt::AlignTop);
	m_layoutMain->addWidget(m_buttonClose, 0, Qt::AlignTop);
	m_layoutMain->setSpacing(0);
	m_layoutMain->setContentsMargins(10, 0, 10, 0);

	// apply the layout
	setLayout(m_layoutMain);
	
}

void LoginTitleBar::initConnect()
{
	// connect slots with signals
	connect(m_buttonMinimized, SIGNAL(clicked()), this, SIGNAL(buttonMinimizedClicked()));
	connect(m_buttonClose, SIGNAL(clicked()), this, SIGNAL(buttonCloseClicked()));
}