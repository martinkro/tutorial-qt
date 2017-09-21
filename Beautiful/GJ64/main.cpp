#include "GJ64.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include<mainwindow.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator translator;
	translator.load("gj64_zh.qm");
	a.installTranslator(&translator);
	
	//GJ64 w;
	//w.show();

	MainWindow mainwin;
	mainwin.show();
	
	return a.exec();
}
