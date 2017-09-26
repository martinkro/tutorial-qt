#include "xprogressindicator.h"
#include <QVBoxLayout>

XProgressIndicatorTimer::XProgressIndicatorTimer(const QString& imagePath, int total, QWidget* parent)
    :QWidget(parent)
{
	m_index = 1;
	m_total = total;
	m_imagePath = imagePath;
	m_labelImage = new QLabel;
	m_labelTip = new QLabel(tr("Waiting ..."));

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget(m_labelImage, 0, Qt::AlignHCenter);
	layoutMain->setSpacing(10);
	layoutMain->addWidget(m_labelTip, 0, Qt::AlignHCenter);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	setLayout(layoutMain);

	m_timer = new QTimer(this);
	m_timer->setInterval(100); // 100 ms
	connect(m_timer, &QTimer::timeout, this, &XProgressIndicatorTimer::updatePixmap);

	// start();
}

void XProgressIndicatorTimer::start()
{
	m_timer->start();
}

void XProgressIndicatorTimer::stop()
{
	m_timer->stop();
}

void XProgressIndicatorTimer::updatePixmap()
{
	m_index++;
	if (m_index > m_total) m_index = 1;
	QPixmap pixmap(m_imagePath.arg(m_index));
	m_labelImage->setPixmap(pixmap);
}

void XProgressIndicatorTimer::setTip(const QString& tip)
{
	m_labelTip->setText(tip);
}