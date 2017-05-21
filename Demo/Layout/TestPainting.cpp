#include "TestPainting.h"
#include <QPainter>
#include <QTimer>
#include <QTextStream>

TestPainting::TestPainting(QWidget *parent)
	: QWidget(parent)
{
}

TestPainting::~TestPainting()
{
}

Lines::Lines(QWidget *parent)
	: QWidget(parent)
{ }

void Lines::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	QPainter qp(this);
	drawLines(&qp);
}

void Lines::drawLines(QPainter *qp) {

	QPen pen(Qt::black, 2, Qt::SolidLine);
	qp->setPen(pen);
	qp->drawLine(20, 40, 250, 40);

	pen.setStyle(Qt::DashLine);
	qp->setPen(pen);
	qp->drawLine(20, 80, 250, 80);

	pen.setStyle(Qt::DashDotLine);
	qp->setPen(pen);
	qp->drawLine(20, 120, 250, 120);

	pen.setStyle(Qt::DotLine);
	qp->setPen(pen);
	qp->drawLine(20, 160, 250, 160);

	pen.setStyle(Qt::DashDotDotLine);
	qp->setPen(pen);
	qp->drawLine(20, 200, 250, 200);

	QVector<qreal> dashes;
	qreal space = 4;

	dashes << 1 << space << 5 << space;

	pen.setStyle(Qt::CustomDashLine);
	pen.setDashPattern(dashes);

	qp->setPen(pen);
	qp->drawLine(20, 240, 250, 240);
}

Colours::Colours(QWidget *parent)
	: QWidget(parent)
{ }

void Colours::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void Colours::doPainting() {

	QPainter painter(this);
	painter.setPen(QColor("#d4d4d4"));

	painter.setBrush(QBrush("#c56c00"));
	painter.drawRect(10, 15, 90, 60);

	painter.setBrush(QBrush("#1ac500"));
	painter.drawRect(130, 15, 90, 60);

	painter.setBrush(QBrush("#539e47"));
	painter.drawRect(250, 15, 90, 60);

	painter.setBrush(QBrush("#004fc5"));
	painter.drawRect(10, 105, 90, 60);

	painter.setBrush(QBrush("#c50024"));
	painter.drawRect(130, 105, 90, 60);

	painter.setBrush(QBrush("#9e4757"));
	painter.drawRect(250, 105, 90, 60);

	painter.setBrush(QBrush("#5f3b00"));
	painter.drawRect(10, 195, 90, 60);

	painter.setBrush(QBrush("#4c4c4c"));
	painter.drawRect(130, 195, 90, 60);

	painter.setBrush(QBrush("#785f36"));
	painter.drawRect(250, 195, 90, 60);
}

Patterns::Patterns(QWidget *parent)
	: QWidget(parent)
{ }

void Patterns::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void Patterns::doPainting() {

	QPainter painter(this);
	painter.setPen(Qt::NoPen);

	painter.setBrush(Qt::HorPattern);
	painter.drawRect(10, 15, 90, 60);

	painter.setBrush(Qt::VerPattern);
	painter.drawRect(130, 15, 90, 60);

	painter.setBrush(Qt::CrossPattern);
	painter.drawRect(250, 15, 90, 60);

	painter.setBrush(Qt::Dense7Pattern);
	painter.drawRect(10, 105, 90, 60);

	painter.setBrush(Qt::Dense6Pattern);
	painter.drawRect(130, 105, 90, 60);

	painter.setBrush(Qt::Dense5Pattern);
	painter.drawRect(250, 105, 90, 60);

	painter.setBrush(Qt::BDiagPattern);
	painter.drawRect(10, 195, 90, 60);

	painter.setBrush(Qt::FDiagPattern);
	painter.drawRect(130, 195, 90, 60);

	painter.setBrush(Qt::DiagCrossPattern);
	painter.drawRect(250, 195, 90, 60);
}

TransparentRectangles::TransparentRectangles(QWidget *parent)
	: QWidget(parent)
{ }

void TransparentRectangles::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void TransparentRectangles::doPainting() {

	QPainter painter(this);

	for (int i = 1; i <= 11; i++) {
		painter.setOpacity(i*0.1);
		painter.fillRect(50 * i, 20, 40, 40, Qt::darkGray);
	}
}

Donut::Donut(QWidget *parent)
	: QWidget(parent)
{ }

void Donut::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void Donut::doPainting() {

	QPainter painter(this);

	painter.setPen(QPen(QBrush("#535353"), 0.5));
	painter.setRenderHint(QPainter::Antialiasing);

	int h = height();
	int w = width();

	painter.translate(QPoint(w / 2, h / 2));

	for (qreal rot = 0; rot < 360.0; rot += 5.0) {
		painter.drawEllipse(-125, -40, 250, 80);
		painter.rotate(5.0);
	}
}

Shapes::Shapes(QWidget *parent)
	: QWidget(parent)
{ }

void Shapes::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void Shapes::doPainting() {

	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(QBrush("#888"), 1));
	painter.setBrush(QBrush(QColor("#888")));

	QPainterPath path1;

	path1.moveTo(5, 5);
	path1.cubicTo(40, 5, 50, 50, 99, 99);
	path1.cubicTo(5, 99, 50, 50, 5, 5);
	painter.drawPath(path1);

	painter.drawPie(130, 20, 90, 60, 30 * 16, 120 * 16);
	painter.drawChord(240, 30, 90, 60, 0, 16 * 180);
	painter.drawRoundRect(20, 120, 80, 50);

	QPolygon polygon({ QPoint(130, 140), QPoint(180, 170), QPoint(180, 140),
		QPoint(220, 110), QPoint(140, 100) });

	painter.drawPolygon(polygon);

	painter.drawRect(250, 110, 60, 60);

	QPointF baseline(20, 250);
	QFont font("Georgia", 55);
	QPainterPath path2;
	path2.addText(baseline, font, "Q");
	painter.drawPath(path2);

	painter.drawEllipse(140, 200, 60, 60);
	painter.drawEllipse(240, 200, 90, 60);
}

LinearGradients::LinearGradients(QWidget *parent)
	: QWidget(parent)
{ }

void LinearGradients::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void LinearGradients::doPainting() {

	QPainter painter(this);

	QLinearGradient grad1(0, 20, 0, 110);

	grad1.setColorAt(0.1, Qt::black);
	grad1.setColorAt(0.5, Qt::yellow);
	grad1.setColorAt(0.9, Qt::black);

	painter.fillRect(20, 20, 300, 90, grad1);

	QLinearGradient grad2(0, 55, 250, 0);

	grad2.setColorAt(0.2, Qt::black);
	grad2.setColorAt(0.5, Qt::red);
	grad2.setColorAt(0.8, Qt::black);

	painter.fillRect(20, 140, 300, 100, grad2);
}

RadialGradient::RadialGradient(QWidget *parent)
	: QWidget(parent)
{ }

void RadialGradient::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void RadialGradient::doPainting() {

	QPainter painter(this);

	int h = height();
	int w = width();

	QRadialGradient grad1(w / 2, h / 2, 80);

	grad1.setColorAt(0, QColor("#032E91"));
	grad1.setColorAt(0.3, Qt::white);
	grad1.setColorAt(1, QColor("#032E91"));

	painter.fillRect(0, 0, w, h, grad1);
}

Puff::Puff(QWidget *parent)
	: QWidget(parent) {

	x = 1;
	opacity = 1.0;
	timerId = startTimer(15);
}

void Puff::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void Puff::doPainting() {

	QPainter painter(this);
	QTextStream out(stdout);

	QString text = "ZetCode";

	painter.setPen(QPen(QBrush("#575555"), 1));

	QFont font("Courier", x, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.width(text);

	painter.setFont(font);

	if (x > 10) {
		opacity -= 0.01;
		painter.setOpacity(opacity);
	}

	if (opacity <= 0) {
		killTimer(timerId);
		out << "timer stopped" << endl;
	}

	int h = height();
	int w = width();

	painter.translate(QPoint(w / 2, h / 2));
	painter.drawText(-textWidth / 2, 0, text);
}

void Puff::timerEvent(QTimerEvent *e) {

	Q_UNUSED(e);

	x += 1;
	repaint();
}
