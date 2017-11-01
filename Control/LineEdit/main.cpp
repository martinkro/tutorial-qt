#include "lineedit.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// add qt style sheet
	QFile file("lineedit.qss");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();
	
	LineEdit w;
	w.show();
	
	return a.exec();
}
