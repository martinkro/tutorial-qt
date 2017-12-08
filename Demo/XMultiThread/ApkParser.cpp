#include "ApkParser.h"
#include "XCommand.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QtCore/QCoreApplication>
#include <QDebug>

ApkParser::ApkParser(QObject* parent)
	:QObject(parent)
{
	qDebug() << "ApkParser constructor";
	QString appDir = qApp->applicationDirPath();
	programPath = appDir + "/tools/aapt.exe";
	programPath = QDir::toNativeSeparators(programPath);
	cmd = new XCommand(this);
	connect(cmd, &XCommand::proc_errorOccurred, [=](int errorCode) {
		qDebug() << "[APK Paser]errorCode:" << errorCode;
		emit parseFinished(101);
	});
	connect(cmd, &XCommand::proc_finished, [=](int exitCode) {
		qDebug() << "[APK Paser]exitCode:" << exitCode;
		if (exitCode == 0)
		{
			parseOutput(cmd->getOutput());
		}
		else
		{
			parseOutput(cmd->getError());
		}
		emit parseFinished(exitCode);
	});
}

ApkParser::~ApkParser()
{
	qDebug() << "ApkParser destructor";
}

void ApkParser::startParse(const QString& apkPath)
{
	initialize();
	QFile file(apkPath);
	if (!file.exists())
	{
		// File Not Exists
		emit parseFinished(2);
	}

	if (!QFileInfo(programPath).exists())
	{
		emit parseFinished(3);
	}

	appSize = file.size();
	this->apkPath = apkPath;

	

	cmd->exec(programPath, QStringList() << "dump" << "badging" << QDir::toNativeSeparators(apkPath));
}

void ApkParser::parseOutput(const QString& data)
{
	//qDebug() << data;
	QStringList lines = data.split("\r\n", QString::SkipEmptyParts);
	int flags = 0;
	for (auto it = lines.begin(); it != lines.end(); it++)
	{
		if (flags == 3)
		{
			break;
		}
		if (it->startsWith("package:"))
		{
			//qDebug() << *it;
			int start = it->indexOf("name='");
			int end = -1;
			if (start != -1)
			{
				end = it->indexOf("'", start + 6);
				this->packageName = it->mid(start + 6, end - start - 6);
				//qDebug() << packageName;
			}


			start = it->indexOf("versionName='");
			if (start != -1)
			{
				end = it->indexOf("'", start + 13);
				this->appVersion = it->mid(start + 13, end - start - 13);
				//qDebug() << appVersion;
			}
			flags |= 1;
		}
		else if (it->startsWith("application-label:"))
		{
			//qDebug() << *it;
			int start = it->indexOf("'");
			int end = it->indexOf("'", start+1);
			this->appName = it->mid(start + 1, end - start - 1);
			//qDebug() << appName;
			flags |= 2;
		}
		
	}
}

void ApkParser::parseError(const QString& data)
{
	qDebug() << data;

}

void ApkParser::initialize() {
	apkPath = "";
	appSize = 0;
	appName = "";
	appVersion = "";
	packageName = "";
}