#pragma once

#include <QtWidgets/QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include "ui_gj360.h"

class GJ360 : public QMainWindow
{
	Q_OBJECT

public:
	GJ360(QWidget *parent = Q_NULLPTR);

private:
	void initFramelessWindow();
	void initFramelessWindow2();

private slots:
	void slot_minWindow();

private:
	Ui::GJ360Class ui;
	bool m_Drag; //记录鼠标是否按下  
	QPoint m_DragPosition;//记录鼠标位置  
						  //重写三个鼠标事件来实现窗口移动  
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
};
