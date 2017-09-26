#include "loginnormal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

LoginNormal::LoginNormal(QWidget* parent)
    :LoginBase(parent)
{
	initUI();
	initConnect();
}

void LoginNormal::initConnect()
{
	connect(m_buttonLogin, SIGNAL(clicked()), this, SIGNAL(login_clicked()));
	connect(m_buttonQRCode, SIGNAL(clicked()), this, SIGNAL(qrcode_clicked()));
}

void LoginNormal::initUI()
{
	m_initUsernameText = tr("QQ Number");
	m_initPasswordText = tr("Password");

	m_lineeditUsername = new QLineEdit;
	m_lineeditUsername->setObjectName("login_username");
	m_lineeditUsername->setText(m_initUsernameText);
	m_lineeditUsername->setFixedSize(250,25);

	m_lineeditPassword = new QLineEdit;
	m_lineeditPassword->setObjectName("login_password");
	m_lineeditPassword->setMaxLength(16);
	m_lineeditPassword->setText(m_initPasswordText);
	m_lineeditPassword->setFixedSize(250, 25);

	m_buttonLogin = new PushButton;
	m_buttonLogin->setButtonBackground(":/login/button/login");
	m_buttonLogin->setText(tr("SIGN IN"));

	m_buttonQRCode = new PushButton;
	m_buttonQRCode->setButtonBackground(":/login/button/qrcode");

	QVBoxLayout* layoutU = new QVBoxLayout;
	layoutU->addWidget(m_lineeditUsername, 0, Qt::AlignHCenter);
	layoutU->addSpacing(10);
	layoutU->addWidget(m_lineeditPassword,0, Qt::AlignHCenter);
	layoutU->setContentsMargins(18, 0, 15, 15);

	QHBoxLayout* layoutB = new QHBoxLayout;
	layoutB->addWidget(new QLabel(), 0, Qt::AlignVCenter | Qt::AlignLeft);
	layoutB->addWidget(m_buttonLogin, 0, Qt::AlignVCenter | Qt::AlignHCenter);
	layoutB->addWidget(m_buttonQRCode,0, Qt::AlignVCenter | Qt::AlignRight);
	layoutB->setContentsMargins(12, 0, 5, 5);

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addLayout(layoutU);
	layoutMain->addLayout(layoutB);
	layoutMain->setContentsMargins(0, 100, 0, 20);
	setLayout(layoutMain);

	this->setContentsMargins(0, 0, 0, 0);


}