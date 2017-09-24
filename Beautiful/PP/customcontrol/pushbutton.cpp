#include "pushbutton.h"
#include <QPainter>

PushButton::PushButton(QWidget *parent)
	: QPushButton(parent)
{

}

void PushButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QString pixmapPath;
	switch (m_status)
	{
	case NORMAL:
		pixmapPath = m_imagePath;
		break;
	case HOVER:
		pixmapPath = tr("%1_hover").arg(m_imagePath);
		break;
	case PRESSED:
		pixmapPath = tr("%1_pressed").arg(m_imagePath);
		break;
	default:
		pixmapPath = m_imagePath;
		break;
	}
	// draw the button background
	painter.drawPixmap(rect(), QPixmap(pixmapPath));  

}

void PushButton::mousePressEvent(QMouseEvent *event)
{
	// only when the left button is pressed we force the repaint
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		m_status = PRESSED;
		update();
	}
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && m_isPressed)
	{
		m_isPressed = false;
		m_status = NORMAL;
		emit clicked();
	}
}

void PushButton::enterEvent(QEvent* event)
{
	m_isPressed = false;
	m_status = HOVER;
}

void PushButton::leaveEvent(QEvent* event)
{
	m_isPressed = false;
	m_status = NORMAL;
}

void PushButton::setButtonBackground(const QString& path)
{
	m_imagePath = path;
	// resize the button to fit the background picture.
	setFixedSize(QPixmap(m_imagePath).size()); 
}