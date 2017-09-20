#include "singleapplication.h"
#include <QWidget>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QFileInfo>
#include <QLibrary>

SingleApplication::SingleApplication(int argc, char** argv)
	: QApplication(argc, argv),
	bRunning(false),
	localServer(NULL),
	mainWindow(NULL)
{
	serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
	initLocalConnection();
}

SingleApplication::~SingleApplication()
{
}

bool SingleApplication::isRunning()
{
	return bRunning;
}

void SingleApplication::newLocalConnection()
{
	QLocalSocket* socket = localServer->nextPendingConnection();
	if (!socket) return;
	socket->waitForReadyRead(1000);
	QTextStream stream(socket);
	delete socket;
	if (mainWindow != NULL)
	{
		mainWindow->raise();
		mainWindow->activateWindow();
		mainWindow->setWindowState((mainWindow->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
		mainWindow->show();
	}
}

void SingleApplication::initLocalConnection()
{
	bRunning = false;
	QLocalSocket socket;
	socket.connectToServer(serverName);
	if (socket.waitForConnected(500))
	{
		bRunning = true;
		// 其他处理，如：将启动参数发送到服务端  
		QTextStream stream(&socket);
		QStringList args = QCoreApplication::arguments();
		if (args.count() > 1)
			stream << args.last();
		else
			stream << QString();
		stream.flush();
		socket.waitForBytesWritten();

		return;
	}

	//连接不上服务器，就创建一个  
	newLocalServer();
}

void SingleApplication::newLocalServer()
{
	localServer = new QLocalServer(this);
	connect(localServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
	if (!localServer->listen(serverName))
	{
		// 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之  
		if (localServer->serverError() == QAbstractSocket::AddressInUseError)
		{
			QLocalServer::removeServer(serverName); // <-- 重点  
			localServer->listen(serverName); // 再次监听  
		}
	}
}
