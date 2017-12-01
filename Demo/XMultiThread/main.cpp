#include <QtCore/QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "Test MultiThread";

	qDebug() << "Test END";

	return a.exec();
}
