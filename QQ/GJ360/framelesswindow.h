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
	
	bool m_Drag; //��¼����Ƿ���  
	QPoint m_DragPosition;//��¼���λ��  
						  //��д��������¼���ʵ�ִ����ƶ�  
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	Ui::FramelessWindow ui;
};
