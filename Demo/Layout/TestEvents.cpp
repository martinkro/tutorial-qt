#include "TestEvents.h"
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QTextStream>
#include <QCheckBox>
#include <QTime>

TestEvents::TestEvents(QObject *parent)
	: QObject(parent)
{
}

TestEvents::~TestEvents()
{
}

Click::Click(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);
	hbox->setSpacing(5);

	QPushButton *quitBtn = new QPushButton("Quit", this);
	hbox->addWidget(quitBtn, 0, Qt::AlignLeft | Qt::AlignTop);

	connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}

KeyPress::KeyPress(QWidget *parent)
	: QWidget(parent)
{ }

void KeyPress::keyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key_Escape) {
		qApp->quit();
	}
}

Move::Move(QWidget *parent)
	: QWidget(parent)
{ }

void Move::moveEvent(QMoveEvent *e) {

	int x = e->pos().x();
	int y = e->pos().y();

	QString text = QString::number(x) + "," + QString::number(y);

	setWindowTitle(text);
}

Disconnect::Disconnect(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);
	hbox->setSpacing(5);

	clickBtn = new QPushButton("Click", this);
	hbox->addWidget(clickBtn, 0, Qt::AlignLeft | Qt::AlignTop);

	QCheckBox *cb = new QCheckBox("Connect", this);
	cb->setCheckState(Qt::Checked);
	hbox->addWidget(cb, 0, Qt::AlignLeft | Qt::AlignTop);

	connect(clickBtn, &QPushButton::clicked, this, &Disconnect::onClick);
	connect(cb, &QCheckBox::stateChanged, this, &Disconnect::onCheck);
}

void Disconnect::onClick() {

	QTextStream out(stdout);
	out << "Button clicked" << endl;
}

void Disconnect::onCheck(int state) {

	if (state == Qt::Checked) {
		connect(clickBtn, &QPushButton::clicked, this, &Disconnect::onClick);
	}
	else {
		disconnect(clickBtn, &QPushButton::clicked, this,
			&Disconnect::onClick);
	}
}

Timer::Timer(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);
	hbox->setSpacing(5);

	label = new QLabel("", this);
	hbox->addWidget(label, 0, Qt::AlignLeft | Qt::AlignTop);

	QTime qtime = QTime::currentTime();
	QString stime = qtime.toString();
	label->setText(stime);

	startTimer(1000);
}

void Timer::timerEvent(QTimerEvent *e) {

	Q_UNUSED(e);

	QTime qtime = QTime::currentTime();
	QString stime = qtime.toString();
	label->setText(stime);
}
