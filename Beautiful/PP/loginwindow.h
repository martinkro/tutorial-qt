#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "customcontrol/xbasewindow.h"
#include "logintitlebar.h"
#include "loginloading.h"
#include "loginnormal.h"
#include "loginqrcode.h"
#include <QPaintEvent>
#include <QStackedWidget>
#include <QVBoxLayout>

class LoginWindow:public XBaseWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget* parent = Q_NULLPTR);
    virtual ~LoginWindow(){}

public:
	void closeEvent(QCloseEvent* event);
protected:
	void paintEvent(QPaintEvent* event);

private:
	void initUI();
	void initConnect();

	enum LOGIN_INDEX{
		LOGIN_QRCODE = 0,
		LOGIN_NORMAL,
		LOGIN_LOADING,
		
	};

private slots:
	void showLoginNormal();
	void showLoginQRCode();
	void showLoginLoading();
	void loginSuccess();
	void loginFailed();

private:
	LoginTitleBar* m_titleBar;
	LoginLoading* m_loginLoading;
	LoginNormal* m_loginNormal;
	LoginQRCode* m_loginQRCode;
	QVBoxLayout* m_layoutMain;
	QStackedWidget* m_center;

	int m_currentIndex;
};

#endif