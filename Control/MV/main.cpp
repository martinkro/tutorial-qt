#include "mv.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MV w;
	w.show();
	return a.exec();
}
