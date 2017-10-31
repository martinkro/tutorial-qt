#include "progress.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>

#include "xprogressindicator.h"
#include "xstoragedisplay.h"
#include "QRoundProgressBar.h"

Progress::Progress(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAutoFillBackground(true);
	QPixmap img("background.png");
	QPalette backgroundPalette;
	backgroundPalette.setBrush(QPalette::Window, QBrush(img));
	setPalette(backgroundPalette);

	// test
	m_progressbar1 = new ProgressBar1;
	m_progressbar2 = new ProgressBar2;

	XProgressIndicator* pi = new XProgressIndicator();
	QPushButton* startPb = new QPushButton("start spin");
	QObject::connect(startPb, SIGNAL(clicked(bool)), pi, SLOT(startAnimation()));

	QPushButton* stopPb = new QPushButton("stop spin");
	QObject::connect(stopPb, SIGNAL(clicked(bool)), pi, SLOT(stopAnimation()));

	XStorageDisplay* storage = new XStorageDisplay;

	QSlider* sl = new QSlider(Qt::Horizontal);
	sl->setMinimum(0);
	sl->setMaximum(100);
	connect(sl, &QSlider::valueChanged, [=](int value) {
		m_progressbar1->setProgress(value);
		m_progressbar2->upd((qreal)sl->value() / sl->maximum());
		storage->setUsedValue(value);
	});

	// test progress indicator
	QSlider* delaySlider = new QSlider;
	delaySlider->setRange(0, 100);
	delaySlider->setValue(pi->animationDelay());
	delaySlider->setOrientation(Qt::Horizontal);
	QObject::connect(delaySlider, SIGNAL(valueChanged(int)), pi, SLOT(setAnimationDelay(int)));
	QVBoxLayout* vbl = new QVBoxLayout;
	vbl->addWidget(startPb);
	vbl->addWidget(stopPb);
	vbl->addWidget(delaySlider);

	QHBoxLayout* hbl = new QHBoxLayout;
	hbl->addWidget(pi);
	hbl->addLayout(vbl);

	// Round ProgressBar
	QRoundProgressBar* round1 = new QRoundProgressBar;
	round1->setFormat("%v");
	round1->setDecimals(0);
	QRoundProgressBar* round2 = new QRoundProgressBar;
	round2->setNullPosition(QRoundProgressBar::PositionRight);
	round2->setBarStyle(QRoundProgressBar::StylePie);
	QRoundProgressBar* round3 = new QRoundProgressBar;
	round3->setFormat("%m");
	round3->setBarStyle(QRoundProgressBar::StyleLine);
	QRoundProgressBar* round4 = new QRoundProgressBar;
	QPalette p1;
	p1.setBrush(QPalette::AlternateBase, Qt::black);
	p1.setColor(QPalette::Text, Qt::yellow);
	round4->setPalette(p1);
	round4->setNullPosition(QRoundProgressBar::PositionLeft);
	round4->setDecimals(0);
	QGradientStops gradientPoints;
	gradientPoints << QGradientStop(0, Qt::green) << QGradientStop(0.5, Qt::yellow) << QGradientStop(1, Qt::red);
	round4->setDataColors(gradientPoints);

	QRoundProgressBar* round5 = new QRoundProgressBar;
	QPalette p2(p1);
	p2.setBrush(QPalette::Base, Qt::lightGray);
	p2.setColor(QPalette::Text, Qt::magenta);
	p2.setColor(QPalette::Shadow, Qt::green);
	round5->setPalette(p2);
	round5->setNullPosition(QRoundProgressBar::PositionRight);
	round5->setBarStyle(QRoundProgressBar::StylePie);
	round5->setDataColors(gradientPoints);


	QRoundProgressBar* round6 = new QRoundProgressBar;
	round6->setDecimals(2);
	round6->setBarStyle(QRoundProgressBar::StyleLine);
	round6->setOutlinePenWidth(18);
	round6->setDataPenWidth(10);


	QRoundProgressBar* round7 = new QRoundProgressBar;
	QPalette palette;
	palette.setBrush(QPalette::Window, Qt::NoBrush);
	palette.setBrush(QPalette::AlternateBase, Qt::NoBrush);
	palette.setBrush(QPalette::Highlight, QBrush(QColor(0, 140, 255)));
	palette.setColor(QPalette::Text, QColor(0, 0, 0));
	round7->setPalette(palette);

	QSlider* sliderRound = new QSlider;
	sliderRound->setOrientation(Qt::Horizontal);
	sliderRound->setRange(0, 100);
	connectToSlider(round1, sliderRound);
	connectToSlider(round2, sliderRound);
	connectToSlider(round3, sliderRound);
	connectToSlider(round4, sliderRound);
	connectToSlider(round5, sliderRound);
	connectToSlider(round6, sliderRound);
	connectToSlider(round7, sliderRound);
	QGridLayout* col1 = new QGridLayout;
	col1->addWidget(round1, 0, 0);
	col1->addWidget(round2, 0, 1);
	col1->addWidget(round3, 0, 2);
	col1->addWidget(sliderRound, 1, 0, 1, 3);
	col1->addWidget(round4, 2, 0);
	col1->addWidget(round5, 2, 1);
	col1->addWidget(round6, 2, 2);

	QGridLayout* col2 = new QGridLayout;
	col2->addWidget(round7, 0, 0, 3, 3);
	QHBoxLayout* row2 = new QHBoxLayout;
	row2->addLayout(col1);
	row2->addLayout(col2);

	// main layout

	QVBoxLayout* v = new QVBoxLayout;
	QHBoxLayout* row1 = new QHBoxLayout;
	row1->addWidget(m_progressbar1);
	row1->addWidget(m_progressbar2);
	row1->addWidget(storage);
	v->addLayout(row1);
	v->addWidget(sl);
	v->addLayout(hbl);
	v->addLayout(row2);
	setLayout(v);

}

void Progress::connectToSlider(QRoundProgressBar* bar, QSlider* slider)
{
	bar->setRange(slider->minimum(), slider->maximum());
	bar->setValue(slider->value());
	connect(slider, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));
}
