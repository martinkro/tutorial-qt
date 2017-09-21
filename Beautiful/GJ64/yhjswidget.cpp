#include "yhjswidget.h"
#include"QLabel"
#include"my360button.h"
#include<QHBoxLayout>
yhjsWidget::yhjsWidget(QWidget*parent) :abstmainwidget(parent)
{

	checkButton *m_btnkjjs = new checkButton(":/image/start_check.png", ":/image/start_uncheck.png", this->downwidget());
	checkButton *m_btnxtjs = new checkButton(":/image/sys_check.png", ":/image/sys_uncheck.png", this->downwidget());
	checkButton *m_btnwljs = new checkButton(":/image/net_check.png", ":/image/net_uncheck.png", this->downwidget());
	checkButton *m_btnypjs = new checkButton(":/image/disk_check.png", ":/image/disk_uncheck.png", this->downwidget());

	m_btnkjjs->setGeometry(55, 80, 150, 150);
	m_btnxtjs->setGeometry(265, 80, 150, 150);
	m_btnwljs->setGeometry(475, 80, 150, 150);
	m_btnypjs->setGeometry(685, 80, 150, 150);


	QFont font;
	font.setFamily("宋体");
	font.setBold(true);
	font.setPixelSize(16);
	QLabel *m_labkjjs = new QLabel("开机加速", this->downwidget());
	QLabel *m_labxtjs = new QLabel("系统加速", this->downwidget());
	QLabel *m_labwljs = new QLabel("网络加速", this->downwidget());
	QLabel *m_labypjs = new QLabel("硬盘加速", this->downwidget());
	m_labkjjs->setStyleSheet("color:rgb(102,102,102);");
	m_labxtjs->setStyleSheet("color:rgb(102,102,102);");
	m_labwljs->setStyleSheet("color:rgb(102,102,102);");
	m_labypjs->setStyleSheet("color:rgb(102,102,102);");

	m_labkjjs->setFont(font);
	m_labxtjs->setFont(font);
	m_labwljs->setFont(font);
	m_labypjs->setFont(font);


	m_labkjjs->setFixedSize(150, 60);
	m_labxtjs->setFixedSize(150, 60);
	m_labwljs->setFixedSize(150, 60);
	m_labypjs->setFixedSize(150, 60);

	m_labkjjs->setGeometry(100, 240, 150, 60);
	m_labxtjs->setGeometry(310, 240, 150, 60);
	m_labwljs->setGeometry(520, 240, 150, 60);
	m_labypjs->setGeometry(730, 240, 150, 60);



	QLabel *m_labkjjs2 = new QLabel("优化软件自启动状态", this->downwidget());
	QLabel *m_labxtjs2 = new QLabel("优化系统和内存设置", this->downwidget());
	QLabel *m_labwljs2 = new QLabel("优化网络配置与性能", this->downwidget());
	QLabel *m_labypjs2 = new QLabel("优化硬盘传输效率", this->downwidget());
	m_labkjjs2->setStyleSheet("color:rgb(124,124,124);");
	m_labxtjs2->setStyleSheet("color:rgb(124,124,124);");
	m_labwljs2->setStyleSheet("color:rgb(124,124,124);");
	m_labypjs2->setStyleSheet("color:rgb(124,124,124);");

	m_labkjjs2->setGeometry(80, 270, 150, 60);
	m_labxtjs2->setGeometry(290, 270, 150, 60);
	m_labwljs2->setGeometry(500, 270, 150, 60);
	m_labypjs2->setGeometry(715, 270, 150, 60);


	QLabel *m_logo = new QLabel(this->topwidget());
	m_logo->setStyleSheet("border-image:url(:/image/logo_speed.png)");
	m_logo->setGeometry(50, 50, 76, 75);


	QFont font2;
	font2.setFamily("黑体");
	font2.setPixelSize(27);
	//  font2.setBold(true);

	QLabel *m_title = new QLabel("一键优化，让电脑快如闪电!", this->topwidget());
	m_title->setStyleSheet("color:white;font:24");
	m_title->setGeometry(150, 60, 400, 32);
	m_title->setFont(font2);

	QLabel *m_title2 = new QLabel("全面提升电脑开机速度,系统速度,上网速度,硬盘速度", this->topwidget());
	m_title2->setStyleSheet("color:white;");
	m_title2->setGeometry(150, 92, 400, 32);


	main3Button *m_btnstartscan = new main3Button(":/image/btn_start_scan.png", this->topwidget());
	m_btnstartscan->setGeometry(700, 50, 164, 64);



	QPushButton *m_btnlow = new QPushButton("启动项(70)", this->downwidget());
	QPushButton *m_btnlow1 = new QPushButton("开机时间", this->downwidget());
	QPushButton *m_btnlow2 = new QPushButton("已忽略(5)", this->downwidget());
	QPushButton *m_btnlow3 = new QPushButton("优化记录(50)", this->downwidget());

	m_btnlow->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow1->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow2->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow3->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");

	m_btnlow->setIcon(QIcon(QPixmap(":/image/yhjs_down1.png")));
	m_btnlow1->setIcon(QIcon(QPixmap(":/image/yhjs_down2.png")));


	m_btnlow->setCursor(Qt::PointingHandCursor);
	m_btnlow1->setCursor(Qt::PointingHandCursor);
	m_btnlow2->setCursor(Qt::PointingHandCursor);
	m_btnlow3->setCursor(Qt::PointingHandCursor);

	m_btnlow->setGeometry(540, 425, 85, 20);
	m_btnlow1->setGeometry(630, 425, 85, 20);
	m_btnlow2->setGeometry(725, 425, 55, 20);
	m_btnlow3->setGeometry(795, 425, 75, 20);

}
