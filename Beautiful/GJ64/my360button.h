#ifndef MY360BUTTON_H
#define MY360BUTTON_H

#include <QObject>
#include <QWidget>
#include<QPaintEvent>
#include<QEvent>
#include<QPushButton>
#include<qpropertyanimation.h>
#include<QDebug>

class mainButton : public QPushButton//用于主的图片
{
	Q_OBJECT
public:
	mainButton(QString pixnormal, QString pixenter, QString pixleave, QWidget*parent);
	~mainButton();
protected:
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
	void paintEvent(QPaintEvent*);

	QPropertyAnimation*m_enteranimation;
	QPropertyAnimation*m_leaveanimation;

	QList<QPixmap> m_enterlist;
	QList<QPixmap> m_leavelist;
	QPixmap m_pixnormal;
	int m_enterIndex;
	int m_leaveIndex;
	bool m_enter;
	bool m_leave;
	public slots:
	void entervaluechange(QVariant var) { m_enterIndex = var.toInt(); update(); }
	void leavevaluechange(QVariant var) { m_leaveIndex = var.toInt(); update(); }
};
class main2Button :public QPushButton//用于4太图片加下文字
{
	Q_OBJECT
public:
	main2Button(QString pixnormal, QString text, QWidget*parent);
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private:
	QPixmap  m_pix;
	QPixmap m_pixborder;
	QString m_text;
	bool m_enter;
};
class main3Button :public QPushButton//用于四态图片
{
	Q_OBJECT
public:
	main3Button(QString pix_listurl, QWidget*parent);
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent*);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e) override;
private:
	QList<QPixmap> m_pixlist;
	int m_index;
	bool m_enter;
};
///////////////////////////////////////////////////////
class headButton :public QPushButton//头像按钮
{
	Q_OBJECT
public:
	headButton(QWidget*parent = 0);
protected:
	void paintEvent(QPaintEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
private:
	QList<QPixmap> m_pixlist;
	int m_index;

};
class wordslineButton :public QPushButton//下划线按钮
{
	Q_OBJECT
public:
	wordslineButton(QString text, QWidget*parent = 0);
protected:
	void paintEvent(QPaintEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
private:
	QString m_text;
	bool m_enter;
};
class checkButton :public QPushButton////////////check优化加速界面下的
{
	Q_OBJECT
public:
	checkButton(QString pixcheckurl, QString pixuncheckurl, QWidget *parent);
protected:
	void paintEvent(QPaintEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
	void mousePressEvent(QMouseEvent*);
private:
	bool m_checked;
	bool m_enter;
	QList<QPixmap> m_checklist;
	QPixmap m_pixcheck;
	QPixmap m_pixuncheck;
	int m_checkindex;
	int m_uncheckindex;


};
class main4Button :public QPushButton//8个图与4个图
{
	Q_OBJECT
public:
	main4Button(QString pixanima, QString pixurl, QWidget*parent = 0);
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
private:
	QList<QPixmap> m_animalist;
	QList<QPixmap> m_normallist;
	QPropertyAnimation *m_animation;
	int animaindex;
	bool m_enter;
	private slots:
	void slot_valuechange(QVariant var) { animaindex = var.toInt(); update(); }
	//  void slot_aniamtion();

};
class cleanMainButton :public QPushButton//清理界面的按钮
{
	Q_OBJECT
public:
	cleanMainButton(QString normal, QString gray, QString aninormal, QString anigray, int number, QWidget *parent);
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void leaveEvent(QEvent *);
private:
	QList<QPixmap> m_pixaninormallist;
	QList<QPixmap> m_pixanigraylist;
	QPixmap m_pixnormal;
	QPixmap m_pixgray;
	int m_normalindex;
	int count;
	QPropertyAnimation *m_aninormal;

	bool m_enter;
	bool m_ischeck;
	private slots:
	void slot_normalaimachange(QVariant var) { m_normalindex = var.toInt(); update(); }

};
class main5Button :public QPushButton//用于四态图片加中间文字
{
	Q_OBJECT
public:
	main5Button(QString pix_listurl, QString text, QWidget*parent);
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent*);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
	QList<QPixmap> m_pixlist;
	int m_index;
	QString m_text;
	bool m_enter;
};

class main6Button :public QPushButton
{
	Q_OBJECT
public:
	main6Button(QString pixurl, QString text, QWidget*parent = 0);
protected:
	void paintEvent(QPaintEvent*);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
private:
	QString m_text;
	QPixmap m_pix;
	bool m_enter;
};






















#endif // MY360BUTTON_H
