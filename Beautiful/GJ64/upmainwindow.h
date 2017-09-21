#ifndef UPMAINWINDOW_H
#define UPMAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"my360button.h"
class UpmainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit UpmainWindow(QWidget *parent = 0);
	main3Button *m_btnmini;
	main3Button *m_btnexit;
	main3Button *m_btnfeedback;
	main3Button *m_btnmenu;
	main3Button *m_btnskin;
	headButton *m_btnhead;
signals:
private:
	public slots :
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	bool    m_MousePressed;
	QPoint  m_MousePos;
	QPoint  m_WindowPos;
};

#endif // UPMAINWINDOW_H
