#ifndef MULTI_CHANNEL_WORKER_H
#define MULTI_CHANNEL_WORKER_H

#include <QObject>
#include <QString>

class QUrl;

class MApkInfo {
public:
	QString apkPath;
	QString appName;
	QString appVersion;
	QString packageName;
	qint64 appSize;
};

Q_DECLARE_METATYPE(MApkInfo);

class MultiChannelWorker:public QObject{
    Q_OBJECT
public:
    MultiChannelWorker(QObject* parent = Q_NULLPTR);
	virtual ~MultiChannelWorker();
signals: 
	void finished();
	void error(int code);
	void item_finished(const MApkInfo& info);
public slots:
    void doWork(const QUrl& inPath,const QUrl& outPath);
private:
};


#endif