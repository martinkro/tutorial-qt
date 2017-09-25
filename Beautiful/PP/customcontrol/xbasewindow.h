#ifndef XBASE_WINDOW_H
#define XBASE_WINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>

class XBaseWindow : public QDialog
{
	Q_OBJECT

public:
	XBaseWindow(QWidget *parent = Q_NULLPTR);
	virtual ~XBaseWindow();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	bool m_isPressed;
	QPoint m_point;
};

#endif
