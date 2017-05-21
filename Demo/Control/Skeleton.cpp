#include "Skeleton.h"
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QApplication>

Skeleton::Skeleton(QWidget *parent)
	: QMainWindow(parent)
{
	QPixmap newpix("new.png");
	QPixmap openpix("open.png");
	QPixmap quitpix("quit.png");

	QAction *quit = new QAction("&Quit", this);

	QMenu *file;
	file = menuBar()->addMenu("&File");
	file->addAction(quit);

	connect(quit, &QAction::triggered, qApp, &QApplication::quit);

	QToolBar *toolbar = addToolBar("main toolbar");
	toolbar->addAction(QIcon(newpix), "New File");
	toolbar->addAction(QIcon(openpix), "Open File");
	toolbar->addSeparator();

	QAction *quit2 = toolbar->addAction(QIcon(quitpix),
		"Quit Application");
	connect(quit2, &QAction::triggered, qApp, &QApplication::quit);

	QTextEdit *edit = new QTextEdit(this);

	setCentralWidget(edit);

	statusBar()->showMessage("Ready");
}

Skeleton::~Skeleton()
{
}
