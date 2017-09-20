#include "gj360.h"
#include <QLabel>
#include <QGraphicsEffect>
#include <QEvent>
#include <QToolButton>

GJ360::GJ360(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initFramelessWindow2();

	// ui.centralWidget->setStyleSheet("#centralWidget{background-image: url(:/img/bg.png);}");
	ui.centralWidget->setStyleSheet("#centralWidget{background-color:blue;}");
}

void GJ360::initFramelessWindow()
{
	this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明  
	setWindowFlags(Qt::FramelessWindowHint); //设置为无外部边框   
	setAttribute(Qt::WA_TranslucentBackground); //设置窗口为透明  设置背景透明，允许鼠标穿透  


	//QLabel* m_pback = new QLabel(this);
	//m_pback->setGeometry(0, 0, this->width() - 10, this->height() - 10);
	//m_pback->setObjectName("MainWidget"); //此处设置ObjectName是为了加载qss效果  
	//QGraphicsDropShadowEffect *Shadow = new QGraphicsDropShadowEffect();
	//Shadow->setBlurRadius(8.0);
	//Shadow->setColor(QColor(63, 63, 63, 180));
	//Shadow->setOffset(8.0);
	//m_pback->setGraphicsEffect(Shadow);
}

void GJ360::initFramelessWindow2()
{
	//去掉窗口边框  
	setWindowFlags(Qt::FramelessWindowHint);
	int width = this->width();
	//构建最小化、最大化、关闭按钮  
	QToolButton *minButton = new QToolButton(this);
	QToolButton *closeButton = new QToolButton(this);
	//获取最小化、关闭按钮图标  
	QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	//设置最小化、关闭按钮图标  
	minButton->setIcon(minPix);
	closeButton->setIcon(closePix);
	//设置最小化、关闭按钮在界面的位置  
	minButton->setGeometry(width - 46, 5, 20, 20);
	closeButton->setGeometry(width - 25, 5, 20, 20);
	//设置鼠标移至按钮上的提示信息  
	minButton->setToolTip(tr("最小化"));
	closeButton->setToolTip(tr("关闭"));
	//设置最小化、关闭按钮的样式  
	minButton->setStyleSheet("background-color:transparent;");
	closeButton->setStyleSheet("background-color:transparent;");
	//关联最小化、关闭按钮的槽函数  
	connect(minButton, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void GJ360::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void GJ360::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton))
	{
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void GJ360::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

void GJ360::slot_minWindow()
{
	this->showMinimized();
}
