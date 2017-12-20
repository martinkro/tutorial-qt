#include "TestObject.h"
#include "TestThread.h"
#include <QDebug>

TestObject::TestObject(QObject* parent)
{
	qDebug() << "Test Object thread id:" << QThread::currentThreadId();
	TestThread* thread = new TestThread;
	connect(thread, SIGNAL(showMessage()), this, SLOT(onShowMessage()));
	thread->start();
}

void TestObject::onShowMessage()
{
	qDebug() << "TestObject::onShowMessage()";
}