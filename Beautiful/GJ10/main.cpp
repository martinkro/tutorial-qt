#include "GJ10.h"
#include "gjmainwindow.h"
#include <QtWidgets/QApplication>

#include "src/test/mainwidget.h"
#include "src/main/mainwindow.h"
#include <QFile>

//#define MAIN_TEST

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//GJ10 w;
	//w.show();

	//GJMainWindow w;
	//w.show();

	QFile qss(":/qss/default");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
#ifdef MAIN_TEST
	MainWidget w;
	w.show();
#else
	MainWindow *w = new MainWindow;
	w->show();
#endif
	
	return a.exec();
}
