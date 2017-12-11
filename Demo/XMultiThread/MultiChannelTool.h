#ifndef MULTI_CHANNEL_TOOL_H
#define MULTI_CHANNEL_TOOL_H

#include <QObject>
#include <QUrl>
#include <QVector>
#include <QString>

class QThread;
class MApkInfo;
class ApkParser;

class MultiChannelTool:public QObject
{
    Q_OBJECT
public:
	enum MCStatus {
		Status_Pending = 0,
		Status_Prepareing = 1,
		Status_Prepare_Finished = 2,
		Status_Doing = 3,
		Status_Done = 4
	};
public:
    MultiChannelTool(const QUrl& inPath,const QUrl& outPath,QObject* parent = Q_NULLPTR);
    MultiChannelTool(const QString& inPath,const QString& outPath,QObject* parent = Q_NULLPTR);
	virtual ~MultiChannelTool();
    
signals:
    void test();
	void prepare_finished(int total, int success);
	void start_process(const QUrl& inPath, const QUrl& outPath);
public:
    void exec();
	void execForThread();
	void cancel();

public slots:
	void onItemFinished(const MApkInfo& info);
	void onPrepareFinished();
	void onPrepareError();
private:
    QUrl m_inPath;
    QUrl m_outPath;
	ApkParser* m_apkParser;
	QVector<QString> m_fileList;
	int m_currentIndex;
	QThread* m_thread;
	MCStatus m_status;
};


#endif