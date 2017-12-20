#include "NumberThread.h"

#include <QDebug>
NumberThread::NumberThread(QObject* parent):
	QThread(parent),
	stop(true),
	abort(false)
{
	start(LowPriority);
}

NumberThread::~NumberThread()
{
	qDebug() << "Number Thread desctructor.";
	abort.store(true);
	stop.store(false);
	QMutexLocker locker(&mutex);
	condition.wakeAll();
	locker.unlock();
	wait();

	qDebug() << "Number Thread end.";
}

void NumberThread::run()
{
	forever
	{
		QMutexLocker locker(&mutex);
		while (stop.load())
		{
			qDebug() << "NumberThread wait ...";
			condition.wait(&mutex);
		}

		if (abort.load())
		{
			return;
		}

		

		for (int i = 0; i < 8; i++)
		{
			QThread::sleep(1);
			emit valueChanged(i);
			if (stop.load())
			{
				qDebug() << "NumberThread stop.";
				condition.wait(&mutex);
			}
		}
	}
}

void NumberThread::startThread()
{
	QMutexLocker locker(&mutex);
	stop.store(false);
	condition.wakeAll();
}

void NumberThread::stopThread()
{
	stop.store(true);
}