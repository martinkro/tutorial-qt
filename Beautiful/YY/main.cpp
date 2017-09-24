#include "yy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	YY w;
	w.show();
	return a.exec();
}
