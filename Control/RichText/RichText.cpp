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
    QMenu* systemMenu = new QMenu(this);
    systemMenu->setObjectName("system");

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
    systemMenu->addAction(aboutAction);
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
	
	QTextDocument* infoDocument = new QTextDocument(tr("html"));
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
	

	QVBoxLayout* main = new QVBoxLayout;
	//main->addWidget(messageLabel, 0, Qt::AlignHCenter);
    main->addLayout(layoutR1,0);
	main->addLayout(layoutText, 0);
	//main->addWidget(textEdit, 0, Qt::AlignHCenter);
	main->addWidget(switchButton, 0, Qt::AlignHCenter);
	QWidget* center = new QWidget;
	center->setLayout(main);
	main->setContentsMargins(32, 0, 32, 25);
	setCentralWidget(center);

	textBrowser->setFixedSize(298,400);
	major->setFixedSize(580, 400);

	setFixedSize(960, 600);
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
