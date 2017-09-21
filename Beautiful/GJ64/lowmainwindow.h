#ifndef LOWMAINWINDOW_H
#define LOWMAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"my360button.h"
class lowMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit lowMainWindow(QWidget *parent = 0);
	mainButton*m_btn;
	mainButton*m_btn1;
	mainButton*m_btn2;
	main2Button *m_btn3;
	main2Button *m_btn4;
	main2Button *m_btn5;
	main2Button *m_btn6;
	main3Button *m_btn7;
signals:

	public slots :
private://按界面顺序的

};

#endif // LOWMAINWINDOW_H
