#include "my360button.h"
#include<QPainter>
#include<QDebug>
#include<QLabel>
#include<QHBoxLayout>
#include<QFontMetrics>
mainButton::mainButton(QString strpixnormal, QString strpixenter, QString strpixleave, QWidget*parent) :QPushButton(parent)
{
	QPixmap pixnormal(strpixnormal);
	QPixmap pixenter(strpixenter);
	QPixmap pixleave(strpixleave);

	setCursor(Qt::PointingHandCursor);
	m_leave = false;
	m_enter = true;
	m_leaveIndex = 0;
	m_enterIndex = 0;
	m_pixnormal = pixnormal;
	for (int i = 0; i<10; i++)//进入
	{
		m_enterlist << pixenter.copy(i*(pixenter.width() / 10), 0, pixenter.width() / 10, pixenter.height());
	}
	for (int j = 0; j<8; j++)//离开
	{
		m_leavelist << pixleave.copy(j*(pixleave.width() / 8), 0, pixleave.width() / 8, pixleave.height());
	}
	m_enteranimation = new QPropertyAnimation(this, "");
	m_enteranimation->setStartValue(0);
	m_enteranimation->setEndValue(9);
	m_enteranimation->setDuration(600);
	connect(m_enteranimation, SIGNAL(valueChanged(QVariant)), this, SLOT(entervaluechange(QVariant)));

	m_leaveanimation = new QPropertyAnimation(this, "");
	m_leaveanimation->setStartValue(0);
	m_leaveanimation->setEndValue(7);
	m_leaveanimation->setDuration(600);
	connect(m_leaveanimation, SIGNAL(valueChanged(QVariant)), this, SLOT(leavevaluechange(QVariant)));
}
mainButton::~mainButton()
{
	delete m_leaveanimation;
	delete m_enteranimation;
}
void mainButton::enterEvent(QEvent *)
{
	m_enter = true;
	m_leave = false;
	m_enteranimation->start();
}
void mainButton::leaveEvent(QEvent *)
{
	m_enter = false;
	m_leave = true;
	m_leaveanimation->start();
}
void mainButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (m_enter)
		painter.drawPixmap(rect(), m_enterlist.at(m_enterIndex));
	if (m_leave)
		painter.drawPixmap(rect(), m_leavelist.at(m_leaveIndex));
}
///////////////////////////////////////////////////////////////////////////////////////////////第二组
main2Button::main2Button(QString pixnormal, QString text, QWidget *parent) :QPushButton(parent)
{
	this->setCursor(Qt::PointingHandCursor);
	m_pix = QPixmap(pixnormal);
	m_text = text;
	m_enter = false;
	QPixmap borpix(":/image/btnborder.png");
	m_pixborder = borpix.copy(2 * (borpix.width() / 3), 0, borpix.width() / 3, borpix.height());//第二个
}
void main2Button::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (m_enter)
		painter.drawPixmap(rect(), m_pixborder);
	painter.drawPixmap(QRect((rect().width() - m_pix.width()) / 2, (rect().height() - m_pix.height()) / 3, m_pix.width(), m_pix.height()), m_pix);

	QFont font;
	QFontMetrics fontmetr(font);
	int m_width = fontmetr.width(m_text);

	painter.setPen(QColor(124, 124, 124));
	painter.drawText(QPoint((rect().width() - m_width) / 2, (rect().height() - m_pix.height()) / 3 + m_pix.height() + 20), m_text);
}
void main2Button::enterEvent(QEvent *)
{
	m_enter = true;
	update();
}
void main2Button::leaveEvent(QEvent *)
{
	m_enter = false;
	update();
}
///////////////////////////////////////////////////////////////////
main3Button::main3Button(QString pixnormal, QWidget *parent) :QPushButton(parent)
{
	this->setCursor(Qt::PointingHandCursor);
	m_index = 0;
	m_enter = false;
	QPixmap pix(pixnormal);
	for (int i = 0; i<4; i++)
		m_pixlist << pix.copy(i*(pix.width() / 4), 0, pix.width() / 4, pix.height());
}
void main3Button::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap((width() - m_pixlist.at(m_index).width()) / 2, (height() - m_pixlist.at(m_index).height()) / 2
		, m_pixlist.at(m_index).width()
		, m_pixlist.at(m_index).height(), m_pixlist.at(m_index));//画图画到中间
}
void main3Button::enterEvent(QEvent *)
{
	m_index = 1;
	m_enter = true;
	update();
}
void main3Button::leaveEvent(QEvent *)
{
	m_index = 0;
	m_enter = false;
	update();
}
void main3Button::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)//如果是左键按下
	{
		m_index = 2;
		update();
		QPushButton::mousePressEvent(e);//返回到上级
	}

}
void main3Button::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)//如果是左键放下
	{
		m_index = 1;
		update();
		QPushButton::mouseReleaseEvent(e);//返回到上级 引出按钮clicked信号
	}

}
/////////////////////////////////////////////////////////头像
headButton::headButton(QWidget*parent) :QPushButton(parent)
{
	setCursor(Qt::PointingHandCursor);
	m_index = 0;
	QPixmap pixheadbor(":/image/head_bkg.png");
	m_pixlist << pixheadbor.copy(0, 0, pixheadbor.width() / 2, pixheadbor.height());
	m_pixlist << pixheadbor.copy(pixheadbor.width() / 2, 0, pixheadbor.width() / 2, pixheadbor.height());

}
void headButton::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), m_pixlist.at(m_index));
	QPixmap pixhead(":/image/head.png");
	painter.drawPixmap((width() - pixhead.width()) / 2, (height() - pixhead.height()) / 2, pixhead.width(), pixhead.height(), pixhead);

}
void headButton::enterEvent(QEvent *)
{
	m_index = 1;
	update();
}
void headButton::leaveEvent(QEvent *)
{
	m_index = 0;
	update();
}
///////////////////////////////////////////////////////////////////
wordslineButton::wordslineButton(QString text, QWidget *parent) :QPushButton(parent)
{
	setCursor(Qt::PointingHandCursor);
	m_text = text;
	m_enter = false;
}
void wordslineButton::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	QFont font;
	QFontMetrics metric(font);
	if (m_enter)
		font.setUnderline(true);
	p.setPen(Qt::white);
	p.setFont(font);
	p.drawText((width() - metric.width(m_text)) / 2, height() / 2, m_text);
}
void wordslineButton::enterEvent(QEvent *)
{
	m_enter = true;
	update();
}
void wordslineButton::leaveEvent(QEvent *)
{
	m_enter = false;
	update();
}
////////////////////////////////////////////////////////////////////////////////////////////
checkButton::checkButton(QString pixcheckurl, QString pixuncheckurl, QWidget *parent) :QPushButton(parent)
{
	setCursor(Qt::PointingHandCursor);
	setFixedSize(150, 150);
	m_checkindex = 4;//checkbox的值
	m_uncheckindex = 0;//checkbox的值
	m_checked = true;
	m_enter = false;

	m_pixcheck = QPixmap(pixcheckurl);
	m_pixuncheck = QPixmap(pixuncheckurl);

	QPixmap pixcheckbox(":/image/cat_checkbox.png");
	for (int i = 0; i<12; i++)
		m_checklist << pixcheckbox.copy(i*(pixcheckbox.width() / 12), 0, pixcheckbox.width(), pixcheckbox.height());

}
void checkButton::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	QPainter p1(this);
	QPixmap m_pixcheckhover(":/image/cat_hover.png");
	QPixmap m_pixuncheckhover(":/image/cat_gray_hover.png");



	if (m_checked)//如果选中了
	{
		if (m_enter)
		{
			p.drawPixmap(rect(), m_pixcheckhover);
			p.drawPixmap(110, 110, m_checklist.at(m_checkindex));
		}
		p1.drawPixmap(rect(), m_pixcheck);
		p1.drawPixmap(110, 110, m_checklist.at(m_checkindex));
	}
	else//如果没选中了
	{
		if (m_enter)
		{
			p.drawPixmap(rect(), m_pixuncheckhover);
			p.drawPixmap(110, 110, m_checklist.at(m_uncheckindex));
		}
		p1.drawPixmap(rect(), m_pixuncheck);
		p1.drawPixmap(110, 110, m_checklist.at(m_uncheckindex));
	}
}
void checkButton::enterEvent(QEvent *)
{
	m_checkindex = 5;//选中的
	m_uncheckindex = 1;//黑色的
	m_enter = true;
	update();
}
void checkButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_checked)
			m_checked = false;
		else
			m_checked = true;
		update();
		QPushButton::mousePressEvent(e);
	}
}
void checkButton::leaveEvent(QEvent *)
{
	m_enter = false;
	m_checkindex = 4;//checkbox的值
	m_uncheckindex = 0;//checkbox的值
	update();
}
////////////////////////////////////////////////////////////////
main4Button::main4Button(QString pixani, QString pixurl, QWidget*parent) :QPushButton(parent)
{
	QPixmap anipix(pixani);
	QPixmap norpix(pixurl);
	for (int i = 0; i<4; i++)
		m_normallist << norpix.copy(i*(norpix.width() / 4), 0, norpix.width() / 4, norpix.height());
	for (int i = 0; i<8; i++)
		m_animalist << anipix.copy(i*(anipix.width() / 8), 0, anipix.width() / 8, anipix.height());
	setCursor(Qt::PointingHandCursor);
	animaindex = 0;
	m_animation = new QPropertyAnimation(this, "");
	m_animation->setStartValue(0);
	m_animation->setEndValue(7);
	m_animation->setDuration(500);
	connect(m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(slot_valuechange(QVariant)));
	m_enter = false;
}
void main4Button::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	if (m_enter)
	{
		p.drawPixmap(rect(), m_animalist.at(animaindex));
	}
	else
	{
		p.drawPixmap(rect(), m_normallist.at(0));
	}
}
void main4Button::enterEvent(QEvent *)
{
	m_enter = true;
	m_animation->start();
}
void main4Button::leaveEvent(QEvent *)
{
	m_enter = false;
	update();
}
///////////////////////////////////////////////////////////////////////////////////////
cleanMainButton::cleanMainButton(QString normal, QString gray, QString aninormal, QString anigray, int number, QWidget *parent) :QPushButton(parent)
{
	m_pixnormal = QPixmap(normal);
	m_pixgray = QPixmap(gray);

	QPixmap pixani(aninormal);
	QPixmap pixanigray(anigray);
	count = number;
	for (int i = 0; i<count; i++)//正常
		m_pixaninormallist << pixani.copy(i*(pixani.width() / count), 0, pixani.width() / count, pixani.height());
	for (int i = 0; i<count; i++)//gray
		m_pixanigraylist << pixanigray.copy(i*(pixanigray.width() / count), 0, pixanigray.width() / count, pixanigray.height());

	setCursor(Qt::PointingHandCursor);

	m_enter = false;
	m_ischeck = true;
	m_normalindex = 0;

	m_aninormal = new QPropertyAnimation(this, "");
	m_aninormal->setStartValue(0);
	m_aninormal->setEndValue(count - 1);
	m_aninormal->setDuration(1200);
	connect(m_aninormal, SIGNAL(valueChanged(QVariant)), this, SLOT(slot_normalaimachange(QVariant)));
}
void cleanMainButton::paintEvent(QPaintEvent *)
{
	QPixmap pixcheck(":/image/clean/group_check.png");
	QPixmap pixuncheck(":/image/clean/group_uncheck.png");

	QPixmap pixcheck_hoverborder(":/image/clean/select_hover.png");
	QPixmap pixcheckborder(":/image/clean/select_normal.png");

	QPixmap pixuncheck_hoverborder(":/image/clean/notselect_hover.png");
	QPixmap pixuncheckborder(":/image/clean/notselect_normal.png");
	QPainter p(this);
	QPainter p2(this);
	if (m_enter)//如果进入就启动动画
	{
		if (m_ischeck)//选中动画

		{
			p.drawPixmap((width() - pixcheckborder.width()) / 2, (height() - pixcheckborder.height()) / 2, pixcheckborder);
			p2.drawPixmap((width() - pixcheck_hoverborder.width()) / 2, (height() - pixcheck_hoverborder.height()) / 2, pixcheck_hoverborder);
			p.drawPixmap((width() - m_pixaninormallist.at(m_normalindex).width()) / 2, (height() - m_pixaninormallist.at(m_normalindex).height()) / 2
				, m_pixaninormallist.at(m_normalindex));
			p.drawPixmap(width() - pixcheck.width(), height() - 1.5*(pixcheck.height()), pixcheck);
		}
		else//非选中动画
		{
			p.drawPixmap((width() - pixuncheckborder.width()) / 2, (height() - pixuncheckborder.height()) / 2, pixuncheckborder);
			p2.drawPixmap(rect(), pixuncheck_hoverborder);
			p.drawPixmap((width() - m_pixanigraylist.at(m_normalindex).width()) / 2, (height() - m_pixanigraylist.at(m_normalindex).height()) / 2
				, m_pixanigraylist.at(m_normalindex));
			p.drawPixmap(width() - pixuncheck.width(), height() - 1.5*(pixuncheck.height()), pixuncheck);
		}
	}
	else//如果不进入
	{
		if (m_ischeck)//如果是选中就做选中动画//起始位置
		{
			p.drawPixmap((width() - m_pixnormal.width()) / 2, (height() - m_pixnormal.height()) / 2, m_pixnormal);
			p.drawPixmap(width() - pixcheck.width(), height() - 1.5*(pixcheck.height()), pixcheck);
		}
		else
		{
			p.drawPixmap((width() - m_pixgray.width()) / 2, (height() - m_pixgray.height()) / 2, m_pixgray);
			p.drawPixmap(width() - pixuncheck.width(), height() - 1.5*(pixuncheck.height()), pixuncheck);
		}
	}
}
void cleanMainButton::enterEvent(QEvent *)
{
	m_enter = true;
	m_aninormal->start();
}
void cleanMainButton::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_ischeck)
			m_ischeck = false;
		else
			m_ischeck = true;
		m_aninormal->start();
		QPushButton::mousePressEvent(e);
	}
}
void cleanMainButton::leaveEvent(QEvent *)//如果离开
{
	m_enter = false;
	m_aninormal->stop();
	m_normalindex = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
main5Button::main5Button(QString pixnormal, QString text, QWidget *parent) :QPushButton(parent)
{
	this->setCursor(Qt::PointingHandCursor);
	m_index = 0;
	m_enter = false;
	QPixmap pix(pixnormal);
	for (int i = 0; i<4; i++)
		m_pixlist << pix.copy(i*(pix.width() / 4), 0, pix.width() / 4, pix.height());
	m_text = text;
	setStyleSheet("main5Button{color:rgb(36,147,229)}"
		"main5Button::hover{color:rgb(36,147,229,180)}");
}
void main5Button::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap((width() - m_pixlist.at(m_index).width()) / 2, (height() - m_pixlist.at(m_index).height()) / 2
		, m_pixlist.at(m_index).width()
		, m_pixlist.at(m_index).height(), m_pixlist.at(m_index));//画图画到中间
	QFont font;
	QFontMetrics metri(font);
	painter.setPen(QColor(36, 147, 229));

	int w = metri.width(m_text);
	painter.drawText((width() - w) / 2 + 5, 16, m_text);
}
void main5Button::enterEvent(QEvent *)
{
	m_index = 1;
	update();
}
void main5Button::leaveEvent(QEvent *)
{
	m_index = 0;
	m_enter = false;
	update();
}
void main5Button::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)//如果是左键按下
	{
		m_index = 2;
		update();
		QPushButton::mousePressEvent(e);
	}
}
void main5Button::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)//如果是左键放下
	{
		m_index = 1;
		update();
		QPushButton::mouseReleaseEvent(e);
	}
}
////////////////////////////////////////////////////////////////////////////
main6Button::main6Button(QString pixurl, QString text, QWidget*parent) :QPushButton(parent)//一个图片with 下文字
{
	setStyleSheet("background:transparent");
	m_pix = QPixmap(pixurl);
	m_text = text;
	m_enter = false;
}
void main6Button::paintEvent(QPaintEvent *e)
{
	QPainter p(this);
	if (m_enter)
	{
		p.setBrush(QColor(242, 242, 242));
		p.drawRect(-1, -1, width() + 1, height() + 1);
	}
	p.drawPixmap((width() - m_pix.width()) / 2, 15, m_pix);
	p.setPen(QColor(88, 88, 88));
	QFont font;
	QFontMetrics metric(font);
	int w = metric.width(m_text);
	p.drawText((width() - w) / 2, 70, m_text);
	QPushButton::paintEvent(e);
}
void main6Button::enterEvent(QEvent *)
{
	m_enter = true;
	update();
}
void main6Button::leaveEvent(QEvent *)
{
	m_enter = false;
	update();
}
