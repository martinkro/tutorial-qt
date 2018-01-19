#include "RichText.h"
#include "PopupMenu.h"
#include "MenuItem.h"

#include "LoginPage.h"
#include "ProtectorPage.h"
#include "TestPage.h"

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
#include <QStackedWidget>
#include <QDebug>
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

    initUi();
    
}

void RichText::initUi()
{
    createTitleBar();

    // pages
    contentStackedWidget = new QStackedWidget;
    contentStackedWidget->setObjectName("content");
    loginPage = new LoginPage;
    protectorPage = new ProtectorPage;
    testPage = new TestPage;
    contentStackedWidget->addWidget(testPage);
    contentStackedWidget->addWidget(protectorPage);
    contentStackedWidget->addWidget(loginPage);

    contentStackedWidget->setCurrentWidget(protectorPage);

    // main
    QVBoxLayout* main = new QVBoxLayout;
    main->setContentsMargins(0, 0, 0, 0);
    main->setSpacing(0);
    main->addWidget(titleWidget, 0);
    main->addWidget(contentStackedWidget, 1);

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

void RichText::createTitleBar()
{
    // Title

    static QMap<int, QString> textMap = {
        {PageIndexLogin,tr("login")},
        {PageIndexProtector,tr("protector")},
        {PageIndexTest,tr("test")},
        {PageIndexSignature,tr("signature")},
        {PageIndexHelp,tr("help")}
    };

    static QMap<int, QString> nameMap = {
        { PageIndexLogin,"login" },
        { PageIndexProtector,"protector" },
        { PageIndexTest,"test" },
        { PageIndexSignature,"signature" },
        { PageIndexHelp,"help" }
    };

    static QList<PageIndex> pageList = { PageIndexLogin,PageIndexProtector,PageIndexTest };
    QButtonGroup* group = new QButtonGroup(this);
    group->setExclusive(true);
    titleToolBar = new QWidget;
    titleToolBar->setObjectName("toolbar");
    QHBoxLayout* layoutToolBar = new QHBoxLayout(titleToolBar);
    layoutToolBar->setContentsMargins(0, 0, 0, 0);
    layoutToolBar->setSpacing(0);
    for (auto index : pageList)
    {
        QString text = textMap.value(index);
        QString name = nameMap.value(index);
        QToolButton* toolbutton = new QToolButton;
        toolbutton->setProperty("xclass", "tab");
        toolbutton->setObjectName(name);
        toolbutton->setText(text);
        toolbutton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolbutton->setCheckable(true);
        toolbutton->setChecked(false);
        if (index == PageIndexTest)
        {
            toolbutton->setChecked(true);
        }
        connect(toolbutton, &QToolButton::clicked, [=]() {
            toolbutton->update();
            onSwitchPage(index); 
        });
        group->addButton(toolbutton);
        layoutToolBar->addWidget(toolbutton);
    }
    titleToolBar->setLayout(layoutToolBar);

    QLabel* logoLabel = new QLabel;
    logoLabel->setObjectName("logo");

    QHBoxLayout* layoutTitle = new QHBoxLayout;
    layoutTitle->setContentsMargins(0, 0, 0, 0);
    layoutTitle->setSpacing(0);
    layoutTitle->addWidget(logoLabel);
    layoutTitle->addStretch();
    layoutTitle->addWidget(titleToolBar);
    layoutTitle->addStretch();
    titleWidget = new QWidget;
    titleWidget->setObjectName("title");
    titleWidget->setLayout(layoutTitle);
}

void RichText::onSwitchPage(PageIndex index)
{
    qDebug() << "RichText::onSwitchPage:" << index;
    switch (index)
    {
    case PageIndexLogin:
        contentStackedWidget->setCurrentWidget(loginPage);
        break;
    case PageIndexProtector:
        contentStackedWidget->setCurrentWidget(protectorPage);
        break;
    case PageIndexTest:
        contentStackedWidget->setCurrentWidget(testPage);
        break;
    default:
        break;
    }
}