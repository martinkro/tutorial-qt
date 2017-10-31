#include "progressbar2.h"
#include <QPainter>


ProgressBar2::ProgressBar2(QWidget *parent)
	: QWidget(parent)
{
	p = 0;
	setMinimumSize(208, 208);
}

ProgressBar2::~ProgressBar2()
{
}

void ProgressBar2::paintEvent(QPaintEvent*)
{
	qreal pd = p * 360;
	qreal rd = 360 - pd;
	QPainter p(this);
	p.fillRect(rect(), Qt::white);
	p.translate(4, 4);
	p.setRenderHint(QPainter::Antialiasing);
	QPainterPath path, path2;
	path.moveTo(100, 0);
	path.arcTo(QRectF(0, 0, 200, 200), 90, -pd);
	QPen pen, pen2;
	pen.setCapStyle(Qt::FlatCap);
	pen.setColor(Qt::blue);
	pen.setWidth(8);
	p.strokePath(path, pen);
	path2.moveTo(100, 0);
	pen2.setWidth(8);
	pen2.setColor(Qt::green);
	pen2.setCapStyle(Qt::FlatCap);
	pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
	path2.arcTo(QRectF(0, 0, 200, 200), 90, rd);
	pen2.setDashOffset(2.2);
	p.setPen(pen2);
	p.drawPath(path2);
}
