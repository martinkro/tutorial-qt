#include "label.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator_zh;
	translator_zh.load(QString("label_zh.qm"));
	a.installTranslator(&translator_zh);

	QFile file("label.qss");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();


	Label w;
	w.show();
	return a.exec();
}
