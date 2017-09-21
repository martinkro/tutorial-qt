#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H
#include<QPaintEvent>
#include <QObject>
#include <QWidget>
#include<QMenu>
#include<QAction>
class trayIconMenu :public QMenu
{
	Q_OBJECT
public:
	trayIconMenu(QWidget *parent = 0);
	void initlevel0();
	void initlevel1();
	void initlevel2();
	void initlevel3();
	void initlevel4();
	void initlevel5();

protected:
	void paintEvent(QPaintEvent *);
private:
	QWidget *m_widlevel0;
	QWidget *m_widmain;

};


class level4Widget :public QWidget
{
public:
	level4Widget(QWidget*parent = 0);
private:
protected:
	void paintEvent(QPaintEvent*);
};

class level5Widget :public QWidget
{
public:
	level5Widget(QWidget*parent = 0);
private:
protected:
	void paintEvent(QPaintEvent*);
};





#endif // TRAYICONMENU_H
