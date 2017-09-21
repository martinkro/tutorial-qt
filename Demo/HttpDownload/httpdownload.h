#pragma once

#include <QtWidgets/QDialog>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QProgressDialog>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include "ui_httpdownload.h"

class HttpDownload : public QDialog
{
	Q_OBJECT

public:
	explicit HttpDownload(QWidget *parent = 0);
	~HttpDownload();

public:
	void startRequest(QUrl url);
private slots:
	void on_downloadButton_clicked();

	void on_quitButton_clicked();

	void on_urlEdit_returnPressed();

	// slot for readyRead() signal
	void httpReadyRead();

	// slot for finished() signal from reply
	void httpDownloadFinished();

	// slot for downloadProgress()
	void updateDownloadProgress(qint64, qint64);

	void enableDownloadButton();
	void cancelDownload();

private:
	Ui::HttpDownloadClass ui;
	QUrl url;
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
	QProgressDialog *progressDialog;
	QFile *file;
	bool httpRequestAborted;
	qint64 fileSize;
};
