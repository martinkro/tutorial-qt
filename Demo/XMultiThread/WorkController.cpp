#include "WorkController.h"
#include "WorkerObject1.h"
#include <QDebug>

WorkController::WorkController(QObject* parent) :
	QObject(parent)
{
	WorkerObject1* worker = new WorkerObject1;
	worker->moveToThread(&workerThread);

	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &WorkController::doWork1, worker, &WorkerObject1::onDoWork1);
	connect(worker, &WorkerObject1::work1Done, this, &WorkController::onWork1Done);

	workerThread.start();
}

WorkController::~WorkController()
{
	workerThread.quit();
	workerThread.wait();
}

void WorkController::onWork1Done(const QString& message)
{
	qDebug() << "WorkController::onWork1Done()" << QThread::currentThreadId();
	qDebug() << message;
}

void WorkController::test()
{
	for (int i = 0; i < 5; i++)
	{
		emit doWork1(QString::number(i));
	}
}