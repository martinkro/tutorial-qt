#include "Sample.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//Sample w;
	//w.show();

	QWidget window;
	window.resize(250, 150);
	window.setWindowTitle("Sample");
	window.show();
	
	return a.exec();
}
