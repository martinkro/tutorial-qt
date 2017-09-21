#include "GJ10.h"
#include "gjmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//GJ10 w;
	//w.show();

	GJMainWindow w;
	w.show();
	
	return a.exec();
}
