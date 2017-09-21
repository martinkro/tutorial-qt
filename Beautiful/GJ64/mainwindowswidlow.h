#ifndef MAINWINDOWSWIDLOW_H
#define MAINWINDOWSWIDLOW_H

#include <QObject>
#include <QWidget>
#include<qpainter.h>
class mainwindowswidlow : public QWidget
{
	Q_OBJECT
public:
	explicit mainwindowswidlow(QWidget *parent = 0);
	bool m_ispaint2;
protected:
	void paintEvent(QPaintEvent *);
signals:

	public slots :
};

#endif // MAINWINDOWSWIDLOW_H
