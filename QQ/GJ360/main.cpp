#include "gj360.h"
#include "singleapplication.h"
#include "framelesswindow.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>

int test_single_instance(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QSharedMemory shared_memory;
	shared_memory.setKey(QString("QQ360"));
	if (shared_memory.attach())
	{
		return 0;
	}
	if (shared_memory.create(QSharedMemory::ReadWrite))
	{
		GJ360 w;
		w.show();
		return a.exec();
	}
	return 0;
}

int test_singleapplication(int argc, char* argv[])
{
	SingleApplication a(argc, argv);

	if (!a.isRunning())
	{
		GJ360 w;
		//传入一个要激活程序的窗口，当多开时会激活已有进程的窗口，且多开失败  
		a.mainWindow = &w;
		w.show();

		return a.exec();
	}
	return 0;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	// GJ360 w;
	FramelessWindow w;
	w.show();
	return a.exec();
}
