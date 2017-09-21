#ifndef MAINWINDOWSWIDUP_H
#define MAINWINDOWSWIDUP_H

#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QPaintEvent>
#include"my360button.h"

class mainwindowswidup : public QWidget
{
	Q_OBJECT
public:
	explicit mainwindowswidup(QWidget *parent = 0);
	main3Button *m_btnreturn;
protected:
	void paintEvent(QPaintEvent *);

signals:
	private slots :


};

#endif // MAINWINDOWSWIDUP_H
