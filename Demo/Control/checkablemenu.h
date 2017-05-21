#ifndef CHECKABLE_MENU_H
#define CHECKABLE_MENU_H

#include <QMainWindow>
#include <QApplication>

class CheckableMenu : public QMainWindow {

	Q_OBJECT

public:
	CheckableMenu(QWidget *parent = 0);

	private slots:
	void toggleStatusbar();

private:
	QAction *viewst;
};

#endif
