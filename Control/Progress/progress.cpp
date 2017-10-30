#include "progress.h"
#include <QVBoxLayout>
#include <QSlider>

Progress::Progress(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_progressbar1 = new ProgressBar1;
	m_progressbar2 = new ProgressBar2;

	QSlider* sl = new QSlider(Qt::Horizontal);
	sl->setMinimum(0);
	sl->setMaximum(100);
	connect(sl, &QSlider::valueChanged, [=](int value) {
		m_progressbar1->setProgress(value);
		m_progressbar2->upd((qreal)sl->value() / sl->maximum());
	});

	QVBoxLayout* v = new QVBoxLayout;
	v->addWidget(m_progressbar1);
	v->addWidget(m_progressbar2);
	v->addWidget(sl);
	setLayout(v);

}
