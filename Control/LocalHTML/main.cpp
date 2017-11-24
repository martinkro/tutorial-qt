#include "LocalHTML.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LocalHTML w;
	w.show();
	return a.exec();
}
