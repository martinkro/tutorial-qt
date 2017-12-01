#include "InterProcess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	InterProcess w;
	w.show();
	return a.exec();
}
