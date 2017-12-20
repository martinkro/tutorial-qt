#include "MultiThread.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MultiThread::MultiThread(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	editNumber = new QLineEdit;
	editNumber->setReadOnly(true);
	btnStart = new QPushButton(tr("Start"));
	btnStop = new QPushButton(tr("Stop"));
	QHBoxLayout* r1 = new QHBoxLayout;
	r1->addWidget(editNumber);
	r1->addWidget(btnStart);
	r1->addWidget(btnStop);

	QVBoxLayout* main = new QVBoxLayout;
	main->addLayout(r1);

	QWidget* wmain = new QWidget;
	wmain->setLayout(main);

	setCentralWidget(wmain);

	connect(btnStart, &QPushButton::clicked, this, &MultiThread::onStartClicked);
	connect(btnStop, &QPushButton::clicked, this, &MultiThread::onStopClicked);
	connect(&threadNumber, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));

	resize(400, 300);
}

void MultiThread::onValueChanged(int value)
{
	editNumber->setText(QString::number(value));
}
void MultiThread::onStartClicked()
{
	threadNumber.startThread();
}
void MultiThread::onStopClicked()
{
	threadNumber.stopThread();
}
