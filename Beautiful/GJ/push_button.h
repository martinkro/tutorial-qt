#pragma once

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class PushButton : public QPushButton
{
	Q_OBJECT

public:
	explicit PushButton(QWidget *parent = 0);
	~PushButton();

	void loadPixmap(QString pic_name);

protected:

	/**
	*
	* 功能说明
	*    鼠标移进事件
	*
	* 参数说明
	*     QEvent * event    事件
	*
	* 返回值
	*     无
	*
	*/
	void enterEvent(QEvent *);

	/**
	*
	* 功能说明
	*     鼠标移出事件
	*
	* 参数说明
	*     QEvent * event    事件
	*
	* 返回值
	*     无
	*
	*/
	void leaveEvent(QEvent *);

	/**
	*
	* 功能说明
	*     鼠标按下事件
	*
	* 参数说明
	*     QMouseEvent *event    鼠标事件
	*
	* 返回值
	*     无
	*
	*/
	void mousePressEvent(QMouseEvent *event);

	/**
	*
	* 功能说明
	*     鼠标释放事件
	*
	* 参数说明
	*     QMouseEvent *event    鼠标事件
	*
	* 返回值
	*     无
	*
	*/
	void mouseReleaseEvent(QMouseEvent *event);

	/**
	*
	* 功能说明
	*     绘图事件
	*
	* 参数说明
	*     QPaintEvent * event    绘图事件
	*
	* 返回值
	*     无
	*
	*/
	void paintEvent(QPaintEvent *);

private:

	//枚举按钮的几种状态
	enum ButtonStatus { NORMAL, ENTER, PRESS, NOSTATUS };
	ButtonStatus status;
	QPixmap pixmap;

	int btn_width; //按钮宽度
	int btn_height; //按钮高度
	bool mouse_press; //按钮左键是否按下
};
