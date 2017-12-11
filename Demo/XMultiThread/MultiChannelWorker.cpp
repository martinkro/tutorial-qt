#include "MultiChannelWorker.h"
#include "ApkParser.h"
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QDir>

MultiChannelWorker::MultiChannelWorker(QObject* parent) :
	QObject(parent)
{
	qDebug() << "MultiChannelWorker constructor";
}

MultiChannelWorker::~MultiChannelWorker()
{
	qDebug() << "MultiChannelWorker destructor";
}

void MultiChannelWorker::doWork(const QUrl& inPath, const QUrl& outPath)
{
	qDebug() << "DoWork ThreadId:" << QThread::currentThreadId();
	QDir out(outPath.toLocalFile());
	QDir in(inPath.toLocalFile());

	if (!in.exists())
	{
		emit error(-1);
		return;
	}

	if (!out.exists())
	{
		QDir().mkpath(outPath.toLocalFile());
	}

	in.setFilter(QDir::Files);
	in.setNameFilters(QStringList() << "*.apk");
	QFileInfoList list = in.entryInfoList();
	for (int i = 0; i < list.size(); i++)
	{
		const QFileInfo& finfo = list.at(i);
		ApkParser parser;
		parser.startParseBlock(finfo.filePath());
		if (parser.isSuccess())
		{
			QString appName = parser.getAppName();
			if (appName.isEmpty())
			{
				continue;
			}
			MApkInfo info;
			info.apkPath = parser.getApkPath();
			info.appName = parser.getAppName();
			info.appSize = parser.getAppSize();
			info.appVersion = parser.getAppVersion();
			info.packageName = parser.getPackageName();
			emit item_finished(info);
		}
	}
	emit finished();
}