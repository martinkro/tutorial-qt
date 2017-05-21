#include "simplemenu.h"
#include <QMenu>
#include <QMenuBar>

SimpleMenu::SimpleMenu(QWidget *parent)
	: QMainWindow(parent) {

	QAction *quit = new QAction("&Quit", this);

	QMenu *file;
	file = menuBar()->addMenu("&File");
	file->addAction(quit);

	connect(quit, &QAction::triggered, qApp, QApplication::quit);
}