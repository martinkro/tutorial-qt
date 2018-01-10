#include "RichText.h"
#include "PopupMenu.h"
#include "MenuItem.h"
#include <QPushButton>
#include <QLabel>
#include <QTextDocument>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QCheckBox>
#include <QToolButton>
#include <iostream>
#include <QToolButton>
using namespace std;
class A
{
public:
	void print()
	{
		cout << "A constructor 1" << endl;
	}
};

RichText::RichText(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	QPushButton* switchButton = new QPushButton(tr("Switch"));
	QLabel* messageLabel = new QLabel(tr("message"));
    messageLabel->setObjectName("message");
    QPushButton* settingsButton = new QPushButton(tr("Settings"));
    PopupMenu* settingsMenu = new PopupMenu(0,10,this);
    settingsMenu->setObjectName("settings");
    QAction* item1Action = new QAction(QIcon("icon_personal_normal.png"),tr("Item 1"),settingsMenu);
    //QAction* item2Action = new QAction(QIcon("icon_personal_normal.png"), tr("Item 2"), settingsMenu);
    settingsMenu->addAction(item1Action);
    //settingsMenu->addAction(item2Action);
    settingsButton->setMenu(settingsMenu);


    QPushButton* systemButton = new QPushButton(tr("System"));
    //systemButton->setIcon(QIcon("icon_personal_normal.png"));
    systemButton->setObjectName("system");
    PopupMenu* systemMenu = new PopupMenu(0, 10, this);
    systemMenu->setObjectName("system");
    systemMenu->setWindowFlags(systemMenu->windowFlags() | Qt::FramelessWindowHint);
    systemMenu->setAttribute(Qt::WA_TranslucentBackground);

    MenuItem* homeLabel = new MenuItem(tr("Home"),systemMenu);
    homeLabel->setObjectName("home");
    QWidgetAction* homeAction = new QWidgetAction(systemMenu);
    homeAction->setDefaultWidget(homeLabel);
    MenuItem* aboutLabel = new MenuItem(tr("About"), systemMenu);
    aboutLabel->setObjectName("about");
    QWidgetAction* aboutAction = new QWidgetAction(systemMenu);
    aboutAction->setDefaultWidget(aboutLabel);
    //aboutAction->setIcon(QIcon("icon_home_normal.png"));

    QWidgetAction* test1Action = new QWidgetAction(systemMenu);
    QToolButton* test1ToolButton = new QToolButton(systemMenu);
    test1ToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    test1ToolButton->setObjectName("test1");
    test1ToolButton->setText(tr("Home"));
    test1ToolButton->setIcon(QIcon("icon_home_normal.png"));
    test1Action->setDefaultWidget(test1ToolButton);

    connect(test1ToolButton, &QToolButton::clicked, test1Action, &QWidgetAction::triggered);
    systemMenu->addAction(homeAction);
    systemMenu->addSeparator();
    systemMenu->addAction(aboutAction);
    systemMenu->addSeparator();
    systemMenu->addAction(test1Action);
    systemButton->setMenu(systemMenu);

    MenuItem* test1MenuItem = new MenuItem(tr("Test 1"));
    test1MenuItem->setObjectName("test1");

    QHBoxLayout* layoutR1 = new QHBoxLayout;
    layoutR1->addStretch();
    layoutR1->addWidget(messageLabel);
    layoutR1->addWidget(settingsButton);
    layoutR1->addWidget(systemButton,0, Qt::AlignVCenter);
    layoutR1->addWidget(test1MenuItem,0,Qt::AlignVCenter);
    layoutR1->addStretch();
	
	//QTextDocument* infoDocument = new QTextDocument(tr("html"));
	//QTextEdit* textEdit = new QTextEdit;
	//textEdit->setDocument(infoDocument);

	QLabel* textBrowser = new QLabel;
	//textBrowser->setDocument(infoDocument);
	//textBrowser->setFrameStyle(QFrame::NoFrame);
	QString info = getHelpInfo();
    textBrowser->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	textBrowser->setText(info);

	QTextBrowser* major = new QTextBrowser;
	major->setFrameStyle(QFrame::NoFrame);
	QHBoxLayout* layoutText = new QHBoxLayout;
	layoutText->addWidget(major);
	layoutText->addWidget(textBrowser);
	layoutText->setContentsMargins(0, 0, 0, 0);
	layoutText->setSpacing(18);

    QVBoxLayout* layoutContent = new QVBoxLayout;
    layoutContent->setContentsMargins(0, 0, 0, 0);
    layoutContent->setSpacing(0);
    layoutContent->addLayout(layoutR1, 0);
    layoutContent->addLayout(layoutText, 0);
    layoutContent->addWidget(switchButton, 0, Qt::AlignHCenter);
    QWidget* contentWidget = new QWidget;
    contentWidget->setObjectName("content");
    contentWidget->setLayout(layoutContent);
	
    // Title
    QToolButton* protectorToolButton = new QToolButton;
    protectorToolButton->setObjectName("protector");
    protectorToolButton->setProperty("xclass", "tab");
    protectorToolButton->setText(tr("protector"));

    QToolButton* signatureToolButton = new QToolButton;
    signatureToolButton->setObjectName("signature");
    signatureToolButton->setProperty("xclass", "tab");
    signatureToolButton->setText(tr("signature"));

    QToolButton* multichannelToolButton = new QToolButton;
    multichannelToolButton->setObjectName("multichannel");
    multichannelToolButton->setProperty("xclass", "tab");
    multichannelToolButton->setText(tr("multichannel"));

    QToolButton* helpToolButton = new QToolButton;
    helpToolButton->setObjectName("help");
    helpToolButton->setProperty("xclass", "tab");
    helpToolButton->setText(tr("help"));

    QLabel* logoLabel = new QLabel;
    logoLabel->setObjectName("logo");

    QHBoxLayout* layoutTitle = new QHBoxLayout;
    layoutTitle->setContentsMargins(0, 0, 0, 0);
    layoutTitle->setSpacing(0);
    layoutTitle->addWidget(logoLabel);
    layoutTitle->addWidget(protectorToolButton);
    layoutTitle->addWidget(signatureToolButton);
    layoutTitle->addWidget(multichannelToolButton);
    layoutTitle->addWidget(helpToolButton);
    QWidget* titleWidget = new QWidget;
    titleWidget->setObjectName("title");
    titleWidget->setLayout(layoutTitle);

    // main
	QVBoxLayout* main = new QVBoxLayout;
    main->setContentsMargins(0, 0, 0, 0);
    main->setSpacing(0);
    main->addWidget(titleWidget, 0);
    main->addWidget(contentWidget, 1);
	QWidget* mainWidget = new QWidget;
    mainWidget->setObjectName("main");
    mainWidget->setLayout(main);
	setCentralWidget(mainWidget);
}

QString RichText::getHelpInfo()
{
	QFile file("help/multichannel.html");
	QString info;
	if (file.exists())
	{
		if (file.open(QFile::ReadOnly))
		{
			info = file.readAll();
			file.close();
		}
		else
		{
			info =  tr("Open Fail");
		}
	}
	else
	{
		info = tr("Error");
	}
	return info;
}
