#include "WorkerObject1.h"
#include <QDebug>
#include <QThread>

WorkerObject1::WorkerObject1(QObject* parent) :
	QObject(parent)
{
	qDebug() << "WorkerObject1::WorkerObject1() ThreadId:" << QThread::currentThreadId();
}

void WorkerObject1::onDoWork1(const QString& message)
{
	qDebug() << "WorkerObject1::onDoWork1()" << QThread::currentThreadId();
	QThread::sleep(1);
	emit work1Done(message);
}