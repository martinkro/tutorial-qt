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
		//����һ��Ҫ�������Ĵ��ڣ����࿪ʱ�ἤ�����н��̵Ĵ��ڣ��Ҷ࿪ʧ��  
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
