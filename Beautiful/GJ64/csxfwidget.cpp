#include "csxfwidget.h"
#include"qlabel.h"
Csxfwidget::Csxfwidget(QWidget*parent) :abstmainwidget(parent)
{

	QLabel *m_logo = new QLabel(this->topwidget());
	m_logo->setStyleSheet("border-image:url(:/image/logo_normal.png)");
	m_logo->setGeometry(50, 50, 76, 75);


	QFont font2;
	font2.setFamily("黑体");
	font2.setPixelSize(27);
	//  font2.setBold(true);

	QLabel *m_title = new QLabel("您的电脑很安全！", this->topwidget());
	m_title->setStyleSheet("color:white;font:24");
	m_title->setGeometry(150, 60, 400, 32);
	m_title->setFont(font2);

	QLabel *m_title2 = new QLabel("定期木马查杀,漏洞修复,时刻保持电脑健康", this->topwidget());
	m_title2->setStyleSheet("color:white;");
	m_title2->setGeometry(150, 92, 400, 32);


	main3Button *m_btnstartscan = new main3Button(":/image/start_btn.png", this->topwidget());
	m_btnstartscan->setGeometry(700, 50, 164, 64);


	main4Button *m_btn1 = new main4Button(":/image/scan_button_quick_hover.png", ":/image/scan_button_quick.png", downwidget());
	m_btn1->setGeometry(140, 100, 140, 140);

	main4Button *m_btn2 = new main4Button(":/image/scan_button_full_hover.png", ":/image/scan_button_full.png", downwidget());
	m_btn2->setGeometry(380, 100, 140, 140);

	main4Button *m_btn3 = new main4Button(":/image/scan_button_custom_hover.png", ":/image/scan_button_custom.png", downwidget());
	m_btn3->setGeometry(620, 100, 140, 140);


	QLabel *m_labkssm = new QLabel("快速扫描", this->downwidget());
	QLabel *m_labqpsm = new QLabel("全盘扫描", this->downwidget());
	QLabel *m_labzdysm = new QLabel("自定义扫描", this->downwidget());
	m_labkssm->setStyleSheet("color:rgb(68,68,68);font: 13pt 微软雅黑;");
	m_labqpsm->setStyleSheet("color:rgb(68,68,68);font: 13pt 微软雅黑;");
	m_labzdysm->setStyleSheet("color:rgb(68,68,68);font: 13pt 微软雅黑;");


	m_labkssm->setGeometry(175, 250, 150, 24);
	m_labqpsm->setGeometry(415, 250, 150, 24);
	m_labzdysm->setGeometry(650, 250, 150, 24);

	main3Button *m_btn4 = new main3Button(":/image/system_fix.png", downwidget());
	m_btn4->setGeometry(710, 310, 60, 60);
	main3Button *m_btn5 = new main3Button(":/image/system_fix.png", downwidget());
	m_btn5->setGeometry(800, 310, 60, 60);

	QLabel *m_labcgxu = new QLabel("常规修复", downwidget());

	QLabel *m_labldxf = new QLabel("漏动修复", downwidget());
	m_labcgxu->setStyleSheet("color:rgb(68,68,68);font: 14px 微软雅黑;");
	m_labldxf->setStyleSheet("color:rgb(68,68,68);font: 14px 微软雅黑;");
	m_labcgxu->setGeometry(710, 380, 80, 30);
	m_labldxf->setGeometry(800, 380, 80, 30);
	m_labcgxu->adjustSize();
	m_labldxf->adjustSize();



	QLabel *m_lab = new QLabel("已启用查杀引擎：", downwidget());
	m_lab->setStyleSheet("color: rgb(153,153,153)");
	m_lab->setGeometry(25, 423, 100, 24);

	main3Button*m_btndown1 = new main3Button(":/image/engStateBtnAvira.png", downwidget());
	m_btndown1->setGeometry(130, 423, 24, 24);
	main3Button*m_btndown2 = new main3Button(":/image/engStateBtnCloud.png", downwidget());
	m_btndown2->setGeometry(155, 423, 24, 24);
	main3Button*m_btndown3 = new main3Button(":/image/engStateBtnQEX.png", downwidget());
	m_btndown3->setGeometry(180, 423, 24, 24);
	main3Button*m_btndown4 = new main3Button(":/image/engStateBtnQiFa.png", downwidget());
	m_btndown4->setGeometry(205, 423, 24, 24);
	main3Button*m_btndown5 = new main3Button(":/image/engStateBtnQVM.png", downwidget());
	m_btndown5->setGeometry(230, 423, 24, 24);

	main5Button *m_btndown6 = new main5Button(":/image/scan_setting.png", "设置", downwidget());
	m_btndown6->setGeometry(700, 423, 50, 25);

	QPushButton *m_btndown7 = new QPushButton("信任区", downwidget());
	m_btndown7->setGeometry(750, 423, 50, 24);
	m_btndown7->setStyleSheet("QPushButton{background:transparent;color: rgb(0,138,255);}"
		"QPushButton::hover{color: rgb(0,180,255);}");

	QPushButton *m_btndown8 = new QPushButton("恢复区", downwidget());
	m_btndown8->setGeometry(800, 423, 50, 24);
	m_btndown8->setStyleSheet("QPushButton{background:transparent;color: rgb(0,138,255);}"
		"QPushButton::hover{color: rgb(0,180,255);}");

	QPushButton *m_btndown9 = new QPushButton("上报区", downwidget());
	m_btndown9->setGeometry(850, 423, 50, 24);
	m_btndown9->setStyleSheet("QPushButton{background:transparent;color: rgb(0,138,255);}"
		"QPushButton::hover{color: rgb(0,180,255);}");

}
