#include "TestThread.h"
#include <QDebug>

TestThread::TestThread(QObject* parent)
{

}

void TestThread::run()
{
	qDebug() << "TestThread::run() thread id:" << QThread::currentThreadId();
	emit showMessage();
}