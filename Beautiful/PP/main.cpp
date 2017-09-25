#include "pp.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "customcontrol/shadowwindow.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator_zh;
	translator_zh.load(QString("pp_zh.qm"));
	a.installTranslator(&translator_zh);

	// add qt style sheet
	QFile file(":/qss/trojan");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();

	//a.setStyleSheet("border-style:solid;border-width:1px;");

	//PP w;
	//w.show();

	// ShadowWindow w;
	// MainWindow w;
	LoginWindow w;
	w.show();

	return a.exec();
}
