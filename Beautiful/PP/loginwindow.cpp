#include "loginwindow.h"
#include "config.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QIcon>

LoginWindow::LoginWindow(QWidget* parent)
    :XBaseWindow(parent)
{
	initUI();
	initConnect();
}

void LoginWindow::initUI()
{
	setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
	
	m_titleBar = new LoginTitleBar;
	m_center = new QStackedWidget;
	m_loginQRCode = new LoginQRCode;
	m_loginLoading = new LoginLoading;
	m_loginNormal = new LoginNormal;

	m_center->addWidget(m_loginQRCode);
	m_center->addWidget(m_loginNormal);
	m_center->addWidget(m_loginLoading);

	m_center->setCurrentIndex(1);
	m_currentIndex = LOGIN_NORMAL;

	m_layoutMain = new QVBoxLayout;
	m_layoutMain->addWidget(m_titleBar);
	m_layoutMain->addWidget(m_center);
	m_layoutMain->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layoutMain);
}

void LoginWindow::initConnect()
{
	connect(m_loginQRCode, SIGNAL(cancel_clicked()), this, SLOT(showLoginNormal()));
	connect(m_loginNormal, SIGNAL(qrcode_clicked()), this, SLOT(showLoginQRCode()));
	connect(m_loginNormal, SIGNAL(login_clicked()), this, SLOT(showLoginLoading()));
	connect(m_titleBar, SIGNAL(buttonMinimizedClicked()), SLOT(showMinimized()));
	connect(m_titleBar, SIGNAL(buttonCloseClicked()), SLOT(close()));

	connect(m_loginLoading, SIGNAL(login_success()), this, SLOT(loginSuccess()));
	connect(m_loginLoading, SIGNAL(login_fail()), this, SLOT(loginFailed()));
}

void LoginWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(":/background/title_background"));
}

void LoginWindow::showLoginNormal()
{
	if (m_currentIndex == LOGIN_LOADING)
	{
		m_loginLoading->stop();
	}
	m_center->setCurrentIndex(LOGIN_NORMAL);
	m_currentIndex = LOGIN_NORMAL;
}

void LoginWindow::showLoginQRCode()
{
	if (m_currentIndex == LOGIN_LOADING)
	{
		m_loginLoading->stop();
	}
	m_center->setCurrentIndex(LOGIN_QRCODE);
	m_currentIndex = LOGIN_QRCODE;
}

void LoginWindow::showLoginLoading()
{
	m_center->setCurrentIndex(LOGIN_LOADING);
	m_currentIndex = LOGIN_LOADING;
	m_loginLoading->start();
}

void LoginWindow::loginSuccess()
{
	// accepted();
	accept();
	// close();
}

void LoginWindow::loginFailed()
{
	showLoginNormal();
}

void LoginWindow::closeEvent(QCloseEvent* event)
{
	event->accept();
}