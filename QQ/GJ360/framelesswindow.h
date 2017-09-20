#pragma once

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include "ui_framelesswindow.h"

class FramelessWindow : public QWidget
{
	Q_OBJECT

public:
	FramelessWindow(QWidget *parent = Q_NULLPTR);
	~FramelessWindow();
private:
	void initFramelessWindow();
	void initFramelessWindow2();

	private slots:
	void slot_minWindow();

private:
	
	bool m_Drag; //记录鼠标是否按下  
	QPoint m_DragPosition;//记录鼠标位置  
						  //重写三个鼠标事件来实现窗口移动  
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	Ui::FramelessWindow ui;
};
