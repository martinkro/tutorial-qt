#include "controls.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Controls w;
	w.show();
	return a.exec();
}
