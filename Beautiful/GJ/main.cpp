#include "gj.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include "main_widget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//QTranslator translator;
	//translator.load("gj_zh.qm");
	//a.installTranslator(&translator);
	
	//GJ w;
	//w.show();

	QTextCodec *codec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);
	//QTextCodec::setCodecForTr(codec);
	//QTextCodec::setCodecForCStrings(codec);

	QTranslator translator;
	translator.load(QString(":/qm/qt_zh_CN"));
	a.installTranslator(&translator);

	QTranslator translator_zh;
	translator_zh.load(QString(":/qm/360safe_zh.qm"));
	a.installTranslator(&translator_zh);

	QFont font("Î¢ÈíÑÅºÚ", 9);
	a.setFont(font);

	MainWidget main_widget;
	main_widget.showWidget();
	
	return a.exec();
}
