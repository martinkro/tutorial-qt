#include "trojan.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Trojan w;
	w.show();
	return a.exec();
}
