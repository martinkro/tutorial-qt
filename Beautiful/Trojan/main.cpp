#include "trojan.h"
#include <QtWidgets/QApplication>

#include <QStyleFactory>

#include "forms/MainForm/trojanassessment.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	/* set up the basic information for application */
	app.setOrganizationName(QStringLiteral("HUST"));
	app.setApplicationName(QStringLiteral("TrojanDetector"));
	app.setApplicationVersion(QStringLiteral("1.0-alpha"));

	// add qt style sheet
	QFile file(":/Qss/stylesheet");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();
	
	//Trojan w;
	//w.show();

	/* Create the main window */
	TrojanAssessment win;
	win.show();
	
	return app.exec();
}
