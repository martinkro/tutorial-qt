#include "framelesswindow.h"
#include <QLabel>
#include <QGraphicsEffect>
#include <QEvent>
#include <QToolButton>

FramelessWindow::FramelessWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initFramelessWindow2();
}

FramelessWindow::~FramelessWindow()
{
}

void FramelessWindow::initFramelessWindow()
{
	this->setWindowOpacity(1); //��������͸���ȣ�0-1 ��ȫ͸������͸��  
	setWindowFlags(Qt::FramelessWindowHint); //����Ϊ���ⲿ�߿�   
	setAttribute(Qt::WA_TranslucentBackground); //���ô���Ϊ͸��  ���ñ���͸����������괩͸  


												//QLabel* m_pback = new QLabel(this);
												//m_pback->setGeometry(0, 0, this->width() - 10, this->height() - 10);
												//m_pback->setObjectName("MainWidget"); //�˴�����ObjectName��Ϊ�˼���qssЧ��  
												//QGraphicsDropShadowEffect *Shadow = new QGraphicsDropShadowEffect();
												//Shadow->setBlurRadius(8.0);
												//Shadow->setColor(QColor(63, 63, 63, 180));
												//Shadow->setOffset(8.0);
												//m_pback->setGraphicsEffect(Shadow);
}

void FramelessWindow::initFramelessWindow2()
{
	//ȥ�����ڱ߿�  
	setWindowFlags(Qt::FramelessWindowHint);
	int width = this->width();
	//������С������󻯡��رհ�ť  
	QToolButton *minButton = new QToolButton(this);
	QToolButton *closeButton = new QToolButton(this);
	//��ȡ��С�����رհ�ťͼ��  
	QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	//������С�����رհ�ťͼ��  
	minButton->setIcon(minPix);
	closeButton->setIcon(closePix);
	//������С�����رհ�ť�ڽ����λ��  
	minButton->setGeometry(width - 46, 5, 20, 20);
	closeButton->setGeometry(width - 25, 5, 20, 20);
	//�������������ť�ϵ���ʾ��Ϣ  
	minButton->setToolTip(tr("��С��"));
	closeButton->setToolTip(tr("�ر�"));
	//������С�����رհ�ť����ʽ  
	minButton->setStyleSheet("background-color:transparent;");
	closeButton->setStyleSheet("background-color:transparent;");
	//������С�����رհ�ť�Ĳۺ���  
	connect(minButton, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void FramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton))
	{
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

void FramelessWindow::slot_minWindow()
{
	this->showMinimized();
}
