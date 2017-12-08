#include <QtCore/QCoreApplication>
#include <QDebug>

#include "ApkParser.h"

// 进程间通信
// 多线程
// 序列化

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "Test MultiThread";

	ApkParser* apkParser = new ApkParser(qApp);;
	QObject::connect(apkParser, &ApkParser::parseFinished, [=](int exitCode) {

		qDebug() << "Exit Code:" << exitCode;
		qDebug() << apkParser->getAppName();
		qDebug() << apkParser->getAppVersion();
		qDebug() << apkParser->getPackageName();
		if (exitCode == 0)
		{
			apkParser->startParse("f:/Game/7577/t.txt");
		}
		
	});
	apkParser->startParse("f:/Game/7577/test.apk");

	qDebug() << "Test END";
	QString strEnd = "QString END.";
	qDebug() << strEnd;

	return a.exec();
}
