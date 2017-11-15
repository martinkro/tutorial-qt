#include "Scroll.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Scroll w;
	w.show();
	return a.exec();
}
