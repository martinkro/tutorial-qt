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
	void startParseBlock(const QString& apkPath);

	const QString& getApkPath()const { return apkPath; }
	const QString& getAppName()const { return appName; }
	const QString& getAppVersion()const { return appVersion; }
	const QString& getPackageName()const { return packageName; }
	qint64 getAppSize()const { return appSize; }
	bool isSuccess() { return this->result == ApkParser::SUCCESS; }

public:
	enum ParseResult {
		SUCCESS = 0,
		UNKNOWN_ERROR = 1,
		APK_NOT_EXIST = 2,
		EXEC_NOT_EXIST = 3,
		EXEC_ERROR = 4,
		EXIT_CODE_ERROR = 5,
	};

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
	ParseResult result;
};


#endif