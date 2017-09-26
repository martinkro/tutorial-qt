#include "loginloading.h"
#include <QVBoxLayout>

LoginLoading::LoginLoading(QWidget* parent)
    :LoginBase(parent)
{
	m_progress = new XProgressIndicatorTimer(":/login/loading/load_%1", 8);
	m_progress->setTip(tr("Login waiting ..."));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(m_progress, 0, Qt::AlignHCenter);
	layout->setContentsMargins(0, 0, 0, 30);
	setLayout(layout);

	m_timer = new QTimer(this);
	m_timer->setInterval(1000); // 1s
	connect(m_timer, &QTimer::timeout, this, &LoginLoading::loginTimeout);

}

void LoginLoading::loginTimeout()
{
	stop();
	emit login_success();
}



void LoginLoading::start()
{
	m_progress->start();
	m_timer->start();
}

void LoginLoading::stop()
{
	m_timer->stop();
	m_progress->stop();
}