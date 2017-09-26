#include "pp.h"
#include "mainwindow.h"
#include "loginwindow.h"
#include "customcontrol/shadowwindow.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include <QTranslator>
#include <QDialog>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator_zh;
	translator_zh.load(QString("pp_zh.qm"));
	a.installTranslator(&translator_zh);

	// add qt style sheet
	//QFile file(":/qss/trojan");
	//file.open(QFile::ReadOnly);
	//qApp->setStyleSheet(file.readAll());
	//file.close();


	MainWindow mainWin;
	LoginWindow* loginWin = new LoginWindow;
	int ret = loginWin->exec();
	if (ret == QDialog::Accepted)
	{
		delete loginWin;
		
		mainWin.show();
		return a.exec();
	}

	return 0;
	
}
