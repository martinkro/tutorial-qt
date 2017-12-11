#include "InterProcess.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QtWidgets/QApplication>
#include <QDir>
#include <QProcess>

#include "MyLibraryWrapper.h"

InterProcess::InterProcess(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	QLabel* labelApkPath = new QLabel(tr("APK PATH:"));
	QLineEdit* editApkPath = new QLineEdit;
	editApkPath->setReadOnly(true);
	QPushButton* btnParseApk = new QPushButton(tr("Parse APK"));
	QHBoxLayout* layoutApk = new QHBoxLayout;
	layoutApk->addWidget(labelApkPath);
	layoutApk->addWidget(editApkPath);
	layoutApk->addWidget(btnParseApk);

	QWidget* winApk = new QWidget;
	winApk->setLayout(layoutApk);

	QTextEdit* teInfo = new QTextEdit;

	btnTestMyLibrary = new QPushButton(tr("Test My Library"));

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget(winApk);
	layoutMain->addWidget(teInfo);
	layoutMain->addWidget(btnTestMyLibrary);

	

	MyLibraryWrapper *wrapper = new MyLibraryWrapper();
	// This is the magic that tells the wrapper to
	// notify us when it's done. We use a QueuedConnection
	// to make sure Qt delivers the signal in a thread
	// safe manner
	connect(wrapper, SIGNAL(done(const QString& )),
		this, SLOT(wrapperDone(const QString&)),
		Qt::QueuedConnection);
	connect(wrapper, &MyLibraryWrapper::do_finished, this, &InterProcess::wrapperFinished);

	connect(btnTestMyLibrary, &QPushButton::clicked, [=]() {
		btnTestMyLibrary->setEnabled(false);
		wrapper->start();
	});

	//connect(wrapper, &MyLibraryWrapper::do_finished, [=]() {
	//	btnTestMyLibrary->setEnabled(true);
	//});

	QAction* actionFileBrowser = editApkPath->addAction(QIcon("icon/folder_open_48px.png"), QLineEdit::TrailingPosition);
	actionFileBrowser->setToolTip(tr("File Open"));
	connect(actionFileBrowser, &QAction::triggered, [=]() {
		static QString prevDir = tr("");
		QString filename;
		filename = QFileDialog::getOpenFileName(this,
			tr("Select APK PATH"),
			prevDir,
			tr("APK (*.apk)")); //Ñ¡ÔñÂ·¾¶  
		if (filename.isEmpty())
		{
			return;
		}
		else {
			QDir dir = QFileInfo(filename).absoluteDir();
			prevDir = dir.path();
			editApkPath->setText(filename);
		}

	});

	connect(btnParseApk, &QPushButton::clicked, [=]() {
		btnParseApk->setEnabled(false);
		QString appDir = qApp->applicationDirPath();
		QString filename = editApkPath->text();
		if (filename.isEmpty() || !QFileInfo(filename).exists())
		{
			qDebug() << "Filename is invalid";
		}
		else {

			const QString currentPath = QDir::currentPath();
			QString executable = QDir::toNativeSeparators(currentPath + QDir::separator() + "tools/aapt.exe");
			QProcess process;
			process.start(executable, QStringList() << "dump" << "badging" << filename);
			if (!process.waitForStarted())
			{
				qDebug() << "Can not start process";
				teInfo->setText("Can not start process");
			}
			else
			{
				if (!process.waitForFinished())
				{
					qDebug() << "Time out";
					teInfo->setText("Time out");
				}
				else
				{
					QString str(process.readAllStandardOutput());
					teInfo->setText(str);
				}
			}
			
		}
		btnParseApk->setEnabled(true);
	});

	setLayout(layoutMain);

	resize(800, 600);


}

void InterProcess::wrapperDone(const QString& message)
{
	qDebug() << message;
}

void InterProcess :: wrapperFinished()
{
	qDebug() << "Wrapper finished";
	btnTestMyLibrary->setEnabled(true);
}
