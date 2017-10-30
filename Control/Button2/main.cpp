#include "button2.h"
#include <QtWidgets/QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// add qt style sheet
	QFile file("button2.qss");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();

	Button2 w;
	w.show();

	return a.exec();
}
