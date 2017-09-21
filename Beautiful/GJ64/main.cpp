#include "GJ64.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GJ64 w;
	w.show();
	return a.exec();
}
