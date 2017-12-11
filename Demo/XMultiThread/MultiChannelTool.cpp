#include "MultiChannelTool.h"
#include "ApkParser.h"
#include "MultiChannelWorker.h"

#include <QDir>
#include <QDebug>
#include <QThread>

MultiChannelTool::MultiChannelTool(const QUrl& inPath, const QUrl& outPath, QObject* parent)
	:QObject(parent),	
	m_inPath(inPath),
	m_outPath(outPath),
	m_apkParser(new ApkParser()),
	m_fileList(),
	m_currentIndex(0),
	m_thread(new QThread(this)),
	m_status(Status_Pending)
	
{
	qDebug() << "MultiChannelTool constructor";
	connect(m_apkParser, &ApkParser::parseFinished, [&](int exitCode) {
		m_currentIndex++;
		static int success = 0;
		if (exitCode == 0)
		{
			QString apkPath = m_apkParser->getApkPath();
			qint64 apkSize = m_apkParser->getAppSize();
			QString apkVersion = m_apkParser->getAppVersion();
			QString packageName = m_apkParser->getPackageName();
			QString appName = m_apkParser->getAppName();

			qDebug() << "Apk Path:" << apkPath;
			qDebug() << "Apk Name:" << QFileInfo(apkPath).fileName();
			qDebug() << "Apk Size:" << apkSize;
			qDebug() << "Apk Version:" << apkVersion;
			qDebug() << "App Name:" << appName;
			qDebug() << "Package Name:" << packageName;
			success++;
		}
		else
		{
			qDebug() << "Handle Fail:" << exitCode;
		}

		if (m_currentIndex < m_fileList.size())
		{
			m_apkParser->startParse(m_fileList.at(m_currentIndex));
		}
		else {
			emit prepare_finished(m_fileList.size(), success);
		}
	});
}

MultiChannelTool::MultiChannelTool(const QString& inPath,const QString& outPath,QObject* parent)
	:MultiChannelTool(QUrl::fromLocalFile(inPath),QUrl::fromLocalFile(outPath),parent)
{
}

MultiChannelTool::~MultiChannelTool()
{
	qDebug() << "MultiChannelTool destructor";
	disconnect(m_apkParser, &ApkParser::parseFinished, 0,0);
	if (m_apkParser != nullptr)
	{
		delete m_apkParser;
		m_apkParser = nullptr;
	}

	m_thread->quit();
	m_thread->wait();
}

void MultiChannelTool::exec()
{
	QDir out(m_outPath.toLocalFile());
	QDir in(m_inPath.toLocalFile());

	if (!in.exists())
	{
		// handle finished
		return;
	}

	if (!out.exists())
	{
		QDir().mkpath(m_outPath.toLocalFile());
	}

	in.setFilter(QDir::Files);
	in.setNameFilters(QStringList() << "*.apk");
	QFileInfoList list = in.entryInfoList();
	for (int i = 0; i < list.size(); i++)
	{
		const QFileInfo& finfo = list.at(i);
		qDebug() << finfo.fileName();
		qDebug() << finfo.filePath();
		m_fileList.append(finfo.filePath());
		//m_apkParser->startParse(finfo.filePath());
	}

	if (m_fileList.size() <= 0) return;

	m_currentIndex = 0;
	m_apkParser->startParse(m_fileList.at(m_currentIndex));
}

void MultiChannelTool::execForThread()
{
	qDebug() << "execForThread Thread Id:" << QThread::currentThreadId();
	MultiChannelWorker* worker = new MultiChannelWorker();
	worker->moveToThread(m_thread);
	connect(m_thread, &QThread::finished, worker, &QObject::deleteLater);
	//connect(m_thread, &QThread::started, worker, &MultiChannelWorker::doWork);
	connect(worker, &MultiChannelWorker::item_finished, this, &MultiChannelTool::onItemFinished);
	connect(worker, &MultiChannelWorker::finished, this, &MultiChannelTool::onPrepareFinished);
	connect(worker, &MultiChannelWorker::error, this, &MultiChannelTool::onPrepareError);
	//connect(worker, &MultiChannelWorker::doWork, this, &MultiChannelTool::start_process);
	connect(this, &MultiChannelTool::start_process, worker, &MultiChannelWorker::doWork);
	m_thread->start();
	emit start_process(m_inPath,m_outPath);
	m_status = Status_Prepareing;
}

void MultiChannelTool::onItemFinished(const MApkInfo& info)
{
	qDebug() << "OnItemFinished Thread Id:" << QThread::currentThreadId();
	qDebug() << "Thread State:" << m_thread->isRunning();
	qDebug() << "App Name:" << info.appName;
	qDebug() << "App Size:" << info.appSize;
	qDebug() << "Apk Path:" << info.apkPath;
}

void MultiChannelTool::onPrepareError()
{
	qDebug() << "PrepareError Thread Id:" << QThread::currentThreadId();
	m_thread->quit();
	m_thread->wait();
	m_status = Status_Done;
	emit prepare_finished(0, 0);
}

void MultiChannelTool::onPrepareFinished()
{
	qDebug() << "PrepareFinished Thread Id:" << QThread::currentThreadId();
	qDebug() << "Thread State:" << m_thread->isRunning();
	m_thread->quit();
	m_thread->wait();
	m_status = Status_Prepare_Finished;
	emit prepare_finished(1, 1);

	// start handle
}

void MultiChannelTool::cancel()
{
	if (m_status == Status_Prepareing)
	{
		m_thread->quit();
		m_thread->wait();
	}
	else if (m_status == Status_Doing)
	{
		// TODO
	}
}