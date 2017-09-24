#include "titlebar.h"

const int TITLE_BAR_HEIGHT = 110;

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
	
	onButtonTabClicked(tr("0"));
	
}

/*
 * Update the tool buttons' states and signal the parent widget
 * to change corresponding page.
 */
void TitleBar::onButtonTabClicked(const QString& obj)
{
	int index = obj.toInt();

	for (int i = 0; i < m_buttonTabList.count(); ++i)
	{
		XToolButton* btn = m_buttonTabList.at(i);
		// normalize all tool buttons except the one the user clicked.
		btn->setButtonPressed(i==index?true:false);
	}
	emit buttonTabClicked(index);
}

void TitleBar::initUI()
{

	setFixedHeight(TITLE_BAR_HEIGHT);
	m_layoutMain = new QVBoxLayout;
	//////////////////////////////////////////////////////////////////////////
	// initialize top part
	
	m_labelTitle = new QLabel(tr("PP"));
	QFont font = const_cast<QFont&>(m_labelTitle->font());
	font.setBold(true);
	font.setPointSize(10);
	m_labelTitle->setFont(font);
	m_labelTitle->setObjectName("LabelTitle");

	m_buttonSettings = new PushButton;
	m_buttonSettings->setButtonBackground(tr(":/sysbuttons/settings"));
	m_buttonSettings->setToolTip(tr("Settings"));

	m_buttonMinimized = new PushButton;
	m_buttonMinimized->setButtonBackground(tr(":/sysbuttons/min"));
	m_buttonMinimized->setToolTip(tr("Minimize"));

	m_buttonClose = new PushButton;
	m_buttonClose->setButtonBackground(tr(":/sysbuttons/close"));
	m_buttonClose->setToolTip(tr("Close"));

	m_layoutTop = new QHBoxLayout;
	m_layoutTop->addWidget(m_labelTitle, 0, Qt::AlignVCenter);
	m_layoutTop->addStretch();
	m_layoutTop->addWidget(m_buttonSettings, 0, Qt::AlignTop);
	m_layoutTop->addWidget(m_buttonMinimized, 0, Qt::AlignTop);
	m_layoutTop->addWidget(m_buttonClose, 0, Qt::AlignTop);
	m_layoutTop->setSpacing(0);
	m_layoutTop->setContentsMargins(10, 0, 10, 0);

	//////////////////////////////////////////////////////////////////////////
	// initialize bottom part
	m_layoutBottom = new QHBoxLayout;
	QStringList strList;
	strList << ":/tabbuttons/protector" 
			<< ":/tabbuttons/channel" 
			<< ":/tabbuttons/signature"
		    << ":/tabbuttons/history" ;
	QStringList textList;
	textList << tr("Protector") << tr("Channel") << tr("Signature") << tr("History");
	QSignalMapper* sigMapper = new QSignalMapper(this);
	for (int i = 0; i < strList.size(); ++i)
	{
		// create a custom tool button
		XToolButton* btn = new XToolButton(strList.at(i));
		connect(btn, SIGNAL(clicked()), sigMapper, SLOT(map()));
		// set tool buttons' text
		btn->setText(textList.at(i));
		m_buttonTabList.append(btn);
		// establish a mapping between the string and widget pointer.
		sigMapper->setMapping(btn, QString::number(i, 10));
		m_layoutBottom->addWidget(btn, 0, Qt::AlignBottom);
		
	}
	connect(sigMapper, SIGNAL(mapped(const QString&)), this, SLOT(onButtonTabClicked(const QString&)));

	m_labelHust = new QLabel(tr("PP Major"));
	m_labelSecurity = new QLabel(tr("PP Minor"));
	m_labelHust->setObjectName("LabelHust");
	m_labelSecurity->setObjectName("LabelSecurity");
	font = const_cast<QFont&>(m_labelSecurity->font());
	font.setBold(true);
	font.setPointSize(16);
	m_labelHust->setFont(font);
	m_labelSecurity->setFont(font);

	m_layoutLabel = new QVBoxLayout;
	m_layoutLabel->addWidget(m_labelHust, 0, Qt::AlignCenter);
	m_layoutLabel->addWidget(m_labelSecurity, 0, Qt::AlignTop);
	m_layoutLabel->setSpacing(5);

	
	m_layoutBottom->addStretch();
	m_layoutBottom->setSpacing(5);
	m_layoutBottom->addLayout(m_layoutLabel);
	m_layoutBottom->setContentsMargins(15, 0, 20, 0);

	//////////////////////////////////////////////////////////////////////////
	m_layoutMain->addLayout(m_layoutTop);
	m_layoutMain->addLayout(m_layoutBottom);
	m_layoutMain->setSpacing(0);
	m_layoutMain->setContentsMargins(0, 0, 0, 0);

	// apply the layout
	setLayout(m_layoutMain);
	
}

void TitleBar::initConnect()
{
	// connect slots with signals
	connect(m_buttonSettings, SIGNAL(clicked()), this, SIGNAL(buttonSettingsClicked()));
	connect(m_buttonMinimized, SIGNAL(clicked()), this, SIGNAL(buttonMinimizedClicked()));
	connect(m_buttonClose, SIGNAL(clicked()), this, SIGNAL(buttonCloseClicked()));
}