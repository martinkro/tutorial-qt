#include "mainwindowswidup.h"
#include"QPainter"
#include<QDebug>
#include<QStyleOption>
mainwindowswidup::mainwindowswidup(QWidget *parent) : QWidget(parent)
{
	setMinimumSize(900, 150);
	setMaximumSize(900, 150);
	setAutoFillBackground(true);
	setStyleSheet("mainwindowswidup{background:rgb(57,196,44);}");

	QPalette palette;
	palette.setBrush(QPalette::Background, QColor(57, 196, 44));
	this->setPalette(palette);

	m_btnreturn = new main3Button(":/image/return.png", this);
	m_btnreturn->setGeometry(0, 0, 115, 38);

}
void mainwindowswidup::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

