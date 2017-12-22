#include "XLogger.h"
#include <QDir>
#include <QFile>
#include <QtCore/QCoreApplication>
#include <QMutex>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>

XLogger& XLogger::getInstance()
{
	static XLogger instance;
	return instance;
}

XLogger::XLogger(QObject* parent):
	QObject(parent)
{
	const QString LOG_DIR_NAME = "log";
	QString logDirPath = QDir::toNativeSeparators(qApp->applicationDirPath() + QDir::separator() + LOG_DIR_NAME);
	QDir appDir(qApp->applicationDirPath());
	if (!appDir.exists(LOG_DIR_NAME))
	{
		appDir.mkdir(LOG_DIR_NAME);
	}

	this->logFilePath = QDir::toNativeSeparators(logDirPath + QDir::separator() + "mtpclient.log");
	if (QFile::exists(this->logFilePath))
	{
		QFile::remove(this->logFilePath);
	}

	QFile file(this->logFilePath);
	file.open(QIODevice::ReadWrite | QIODevice::Text);
	file.close();
}

QString XLogger::getLogFilePath()const
{
	return logFilePath;
}

void XLogger::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
	static QMutex mutex;
	QMutexLocker locker(&mutex);

	QScopedPointer<QFile> file(new QFile(getInstance().getLogFilePath()));
	file.data()->open(QFile::Append | QFile::Text);
	QTextStream out(file.data());
	out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
	switch (type)
	{
	case QtInfoMsg:
		out << "INF ";
		break;
	case QtDebugMsg:
		out << "DBG ";
		break;
	case QtWarningMsg:
		out << "WRN ";
		break;
	case QtCriticalMsg:
		out << "CRT ";
		break;
	case QtFatalMsg:
		out << "FTL ";
		break;
	}

	out << ":" << message << endl;
	out.flush();
}