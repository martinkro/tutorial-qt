#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RichText.h"

class QStackedWidget;
class LoginPage;
class ProtectorPage;
class TestPage;

enum PageIndex
{
    PageIndexLogin = 0,
    PageIndexProtector = 1,
    PageIndexTest = 2,
    PageIndexSignature = 3,
    PageIndexHelp = 4,
};

class RichText : public QMainWindow
{
	Q_OBJECT

public:
	RichText(QWidget *parent = Q_NULLPTR);

	QString getHelpInfo();

private slots:
    void onSwitchPage(PageIndex index);

private:
    void initUi();
    // title bar
    void createTitleBar();


private:
    QWidget* titleWidget;
    QWidget* titleToolBar; // middle

    QStackedWidget* contentStackedWidget;
    LoginPage* loginPage;
    ProtectorPage* protectorPage;
    TestPage* testPage;
};
