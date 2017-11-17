#include "Scroll.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile file("style.qss");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();

	Scroll w;
	w.show();

	return a.exec();
}
