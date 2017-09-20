#pragma once

#include <QApplication>
class QWidget;
class QLocalServer;
class SingleApplication : public QApplication
{
	Q_OBJECT

public:
	SingleApplication(int argc, char** argv);
	~SingleApplication();

public:
	bool isRunning();
	QWidget* mainWindow;

	private slots:
	void newLocalConnection();

private:
	void initLocalConnection();
	void newLocalServer();
	bool bRunning;
	QLocalServer* localServer;
	QString serverName;
};
