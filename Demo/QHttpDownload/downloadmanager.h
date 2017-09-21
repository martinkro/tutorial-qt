#pragma once

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QStringList>
#include <QTimer>
#include <QUrl>

#include <stdio.h>

class QSslError;
class DownloadManager : public QObject
{
	Q_OBJECT
	QNetworkAccessManager manager;
	QList<QNetworkReply *> currentDownloads;
public:
	DownloadManager(QObject *parent = 0);
	~DownloadManager();
	void doDownload(const QUrl &url);
	QString saveFileName(const QUrl &url);
	bool saveToDisk(const QString &filename, QIODevice *data);

public slots:
	void execute();
	void downloadFinished(QNetworkReply *reply);
	void sslErrors(const QList<QSslError> &errors);
};
