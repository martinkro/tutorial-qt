#include "xbasewindow.h"

XBaseWindow::XBaseWindow(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	m_isPressed = false;
}

XBaseWindow::~XBaseWindow()
{
}

/*
* When the widgets need to be repainted, Qt framework will call
* this function automatically to update the invalid regions on the widgets
* Users can force repaint by calling update() or repaint() directly.
*/
void XBaseWindow::paintEvent(QPaintEvent* event)
{
	// providing a container for painting operations, enabling graphical shapes 
	// to be constructed and reused.

	//const int wh = 0;
	//QPainterPath path;
	//path.setFillRule(Qt::WindingFill);
	//path.addRect(wh, wh, this->width() - wh*2, this->height() - wh*2);

	//QPainter painter(this);
	//painter.setRenderHint(QPainter::Antialiasing, true);  //antialiasing hint
	//painter.fillPath(path, QBrush(Qt::white));

	//QColor color(0, 0, 0, 50);
	//for (int i = 0; i<wh; i++)
	//{
	//	QPainterPath path;
	//	path.setFillRule(Qt::WindingFill);
	//	path.addRect(wh - i, wh - i, this->width() - (wh - i) * 2, this->height() - (wh - i) * 2);
	//	color.setAlpha(150 - qSqrt(i) * 50);
	//	painter.setPen(color);
	//	painter.drawPath(path);
	//}

}

void XBaseWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed)
	{
		// the mouse position relate to screen
		QPoint point = event->globalPos();
		move(point - m_point);
	}

}
void XBaseWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
	}
	// the mouse position relate to the current widget
	// you can use event->pos() to replace it.
	m_point = event->globalPos() - pos();
}
void XBaseWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
}
