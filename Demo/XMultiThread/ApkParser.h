#ifndef APK_PARSER_H
#define APK_PARSER_H

#include <QObject>
#include "XCommand.h"
class ApkParser:public QObject
{
    Q_OBJECT
public:
    ApkParser(QObject* parent = Q_NULLPTR);
	virtual ~ApkParser();
	void startParse(const QString& apkPath);

	const QString& getAppName()const { return appName; }
	const QString& getAppVersion()const { return appVersion; }
	const QString& getPackageName()const { return packageName; }
	qint64 getAppSize()const { return appSize; }

signals:
	void parseFinished(int exitCode);

private:
	void parseOutput(const QString& data);
	void parseError(const QString& data);

	void initialize();

public:
	QString apkPath;
	qint64	appSize;
	QString appName;
	QString appVersion;
	QString packageName;


	QString programPath;
	XCommand* cmd;
};


#endif