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
	* ����˵��
	*    ����ƽ��¼�
	*
	* ����˵��
	*     QEvent * event    �¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void enterEvent(QEvent *);

	/**
	*
	* ����˵��
	*     ����Ƴ��¼�
	*
	* ����˵��
	*     QEvent * event    �¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void leaveEvent(QEvent *);

	/**
	*
	* ����˵��
	*     ��갴���¼�
	*
	* ����˵��
	*     QMouseEvent *event    ����¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void mousePressEvent(QMouseEvent *event);

	/**
	*
	* ����˵��
	*     ����ͷ��¼�
	*
	* ����˵��
	*     QMouseEvent *event    ����¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void mouseReleaseEvent(QMouseEvent *event);

	/**
	*
	* ����˵��
	*     ��ͼ�¼�
	*
	* ����˵��
	*     QPaintEvent * event    ��ͼ�¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void paintEvent(QPaintEvent *);

private:

	//ö�ٰ�ť�ļ���״̬
	enum ButtonStatus { NORMAL, ENTER, PRESS, NOSTATUS };
	ButtonStatus status;
	QPixmap pixmap;

	int btn_width; //��ť���
	int btn_height; //��ť�߶�
	bool mouse_press; //��ť����Ƿ���
};
