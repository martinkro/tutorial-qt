#include "MultiThread.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MultiThread w;
	w.show();
	return a.exec();
}
