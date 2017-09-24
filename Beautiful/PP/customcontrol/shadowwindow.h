#ifndef SHADOW_WINDOW_H
#define SHADOW_WINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>

class ShadowWindow : public QDialog
{
	Q_OBJECT

public:
	ShadowWindow(QWidget *parent = Q_NULLPTR);
	virtual ~ShadowWindow();

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
