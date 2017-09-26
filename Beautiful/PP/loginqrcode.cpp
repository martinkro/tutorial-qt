#include "loginqrcode.h"
#include <QPainter>

LoginQRCode::LoginQRCode(QWidget* parent)
    :LoginBase(parent)
{
	initUI();
	initConnect();
}

void LoginQRCode::paintEvent(QPaintEvent* event)
{
	//QPainter painter(this);
	//painter.drawPixmap(this->rect(), QPixmap(":/login/qrcode/background"));
}

void LoginQRCode::initUI()
{
	m_labelInfo = new QLabel(tr("Scan QRCode with phone"));
	m_labelQRCode = new QLabel;
	m_labelQRCode->setPixmap(QPixmap(":/login/qrcode/qr_default"));
	QVBoxLayout* layoutCenter = new QVBoxLayout;
	layoutCenter->addWidget(m_labelInfo, 0, Qt::AlignHCenter);
	layoutCenter->addSpacing(5);
	layoutCenter->addWidget(m_labelQRCode, 0, Qt::AlignHCenter);
	layoutCenter->setContentsMargins(0, 0, 0, 20);

	m_buttonCancel = new PushButton(tr("Cancel"));
	m_buttonCancel->setButtonBackground(":/login/button/login");
	//QFont font = const_cast<QFont&>(m_buttonCancel->font());
	//font.setBold(true);
	//font.setPointSize(10);
	//m_buttonCancel->setFont(font);
	//m_buttonCancel->setText(tr("Cancel"));

	//QPushButton* cancel = new QPushButton;
	//cancel->setText(tr("Cancel"));

	m_layoutMain = new QVBoxLayout;
	m_layoutMain->addLayout(layoutCenter);
	m_layoutMain->addWidget(m_buttonCancel, 0, Qt::AlignHCenter);
	//m_layoutMain->addWidget(cancel, 0, Qt::AlignHCenter);
	m_layoutMain->setContentsMargins(0, 0, 0, 25);
	setLayout(m_layoutMain);
}

void LoginQRCode::initConnect()
{
	connect(m_buttonCancel, SIGNAL(clicked()), this, SIGNAL(cancel_clicked()));
}