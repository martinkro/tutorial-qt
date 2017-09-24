#include "yy.h"
#include <QtWidgets/QApplication>

#include "widget.h"
#include "login/login.h"
#include <QTextCodec>
#include <iostream>

using namespace std;

void customMessageHandler(QtMsgType type, const char *msg)
{
	QString txt;
	switch (type)
	{
	case QtDebugMsg:
		txt = QString("Debug: %1").arg(msg);
		break;
	case QtWarningMsg:
		txt = QString("Warning: %1").arg(msg);
		break;
	case QtCriticalMsg:
		txt = QString("Critical: %1").arg(msg);
		break;
	case QtFatalMsg:
		txt = QString("Fatal: %1").arg(msg);
		abort();
	}
	QFile outFile("./debuglog.txt");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
	QTextStream ts(&outFile);
	ts << txt << endl;

	//输出到控制台
	QDateTime now = QDateTime::currentDateTime();
	cout << now.toString("hh:mm:ss.zzz").toStdString() << " " << txt.toStdString() << endl;
}


int main(int argc, char *argv[])
{
	//qInstallMsgHandler(customMessageHandler);
	//qInstallMsgHandler(customMessageHandler);
	QApplication a(argc, argv);

	Login *l = new Login();
	Widget w;
	QObject::connect(l, SIGNAL(loginMainWidget(QString)), &w, SLOT(loginMainWidgetFinished(QString)));
	l->show();
	if (l->exec() == QDialog::Accepted) {
		w.show();
		return a.exec();
	}
	else {
		return 0;
	}
	
	//YY w;
	//w.show();
	//
	//return a.exec();
}
