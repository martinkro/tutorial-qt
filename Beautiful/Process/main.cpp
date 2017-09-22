#include "process.h"
#include "src/qapplist.h"
#include <QtWidgets/QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//Process w;
	//w.show();

	QFile file(":/uistyle");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();

	QAppList win;
	win.setWindowIcon(QIcon(":/logo"));
	win.show();

	return a.exec();
}
