#include "progressbar1.h"

#include <QPainter>

ProgressBar1::ProgressBar1(QWidget *parent)
	: QWidget(parent)
{
	progress = 0;
}

ProgressBar1::~ProgressBar1()
{
}

void ProgressBar1::setProgress(int val)
{
	progress = (double)val / 100;
	//yes, it is not very good, the best approach is to
	//create something similar to QProgressBar
	this->update();
}


void ProgressBar1::paintEvent(QPaintEvent *)
{
	QPainter p(this);

	QPen pen;
	pen.setWidth(7);
	pen.setColor(Qt::red);
	p.setPen(pen);

	p.setRenderHint(QPainter::Antialiasing);

	QRectF rectangle(10.0, 20.0, 80.0, 80.0);
	//to understand these magic numbers, look drawArc method in Qt doc
	int startAngle = -90 * 16;
	int spanAngle = progress * 360 * 16;

	p.drawArc(rectangle, startAngle, spanAngle);

	p.drawText(rectangle, Qt::AlignCenter, QString::number(progress * 100) + " %");
}
