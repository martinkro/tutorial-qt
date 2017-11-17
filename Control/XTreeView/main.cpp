#include "XTreeView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XTreeView w;
	w.show();
	return a.exec();
}
