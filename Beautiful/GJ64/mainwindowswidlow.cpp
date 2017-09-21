#include "mainwindowswidlow.h"
#include<QStyleOption>
mainwindowswidlow::mainwindowswidlow(QWidget *parent) : QWidget(parent)
{
	setMinimumSize(900, 450);
	setMaximumSize(900, 450);
	m_ispaint2 = false;
	setStyleSheet("mainwindowswidlow{background-color:rgb(252,252,252)}");
}
void mainwindowswidlow::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);


	QPainter p(this);
	p.setPen(QColor(218, 218, 218));
	p.drawLine(QPoint(0, 418), QPoint(900, 418));
	if (m_ispaint2)
	{
		p.setBrush(QColor(242, 244, 247));
		p.drawRect(0, 418, 900, 600);
	}
}
