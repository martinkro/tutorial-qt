#include <QtCore/QCoreApplication>
#include <QDebug>

#include "ApkParser.h"
#include "MultiChannelTool.h"
#include "MultiChannelWorker.h"

// 进程间通信
// 多线程
// 序列化

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qRegisterMetaType<MApkInfo>();

	{
		MultiChannelTool* t = new MultiChannelTool("f:/Game/MultiChannel", "f:/Game/MultiChannel/o");
		//t->exec();
		t->execForThread();
		QObject::connect(t, &MultiChannelTool::prepare_finished, [&](int total, int success) {
			qDebug() << total << ":" << success;
			delete t;
		});
	}

	//qDebug() << "Test MultiThread";

	//ApkParser* apkParser = new ApkParser(qApp);;
	//QObject::connect(apkParser, &ApkParser::parseFinished, [=](int exitCode) {

	//	qDebug() << "Exit Code:" << exitCode;
	//	qDebug() << apkParser->getAppName();
	//	qDebug() << apkParser->getAppVersion();
	//	qDebug() << apkParser->getPackageName();
	//	if (exitCode == 0)
	//	{
	//		apkParser->startParse("f:/Game/7577/t.txt");
	//	}
	//	
	//});
	//apkParser->startParse("f:/Game/7577/test.apk");

	//qDebug() << "Test END";
	//QString strEnd = "QString END.";
	//qDebug() << strEnd;

	return a.exec();
}
