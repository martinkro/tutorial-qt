#include "TestSplitter.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// add qt style sheet
	QFile file("TestSplitter.qss");
	file.open(QFile::ReadOnly);
	a.setStyleSheet(file.readAll());
	file.close();

	TestSplitter w;
	w.show();
	return a.exec();
}
