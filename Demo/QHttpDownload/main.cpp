#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QtCore>
#include "Downloader.h"
#include "downloadmanager.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << "QT Version:" << qVersion();
	//Downloader d;
	//d.doDownload();

	DownloadManager manager;
	QTimer::singleShot(0, &manager, SLOT(execute()));

	return a.exec();
}
