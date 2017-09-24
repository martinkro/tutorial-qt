#include "pp.h"
#include "mainwindow.h"
#include "customcontrol/shadowwindow.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	

	// add qt style sheet
	QFile file(":/qss/trojan");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();

	//a.setStyleSheet("border-style:solid;border-width:1px;");

	//PP w;
	//w.show();

	// ShadowWindow w;
	MainWindow w;
	w.show();

	return a.exec();
}
