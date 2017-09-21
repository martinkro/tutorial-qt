#include "dnqlwidget.h"
#include"qlabel.h"
#include "my360button.h"
dnqlWidget::dnqlWidget(QWidget*parent) :abstmainwidget(parent)
{
	QLabel *m_lablogo = new QLabel(this->topwidget());
	m_lablogo->setStyleSheet("border-image:url(:/image/logo_clean.png)");
	m_lablogo->setGeometry(40, 40, 90, 90);

	main3Button*m_btnclean = new main3Button(":/image/btn_top_clean.png", this->topwidget());
	m_btnclean->setGeometry(700, 50, 164, 64);


	QFont font2;
	font2.setFamily("黑体");
	font2.setPixelSize(27);
	//  font2.setBold(true);

	QLabel *m_title = new QLabel("已选择6项清理类型", this->topwidget());
	m_title->setStyleSheet("color:white;");
	m_title->setGeometry(150, 60, 400, 32);
	m_title->setFont(font2);

	QLabel *m_title2 = new QLabel("经常清理,让电脑保持最轻松的状态", this->topwidget());
	m_title2->setStyleSheet("color:white;");
	m_title2->setGeometry(150, 92, 400, 32);

	downwidget()->m_ispaint2 = true;
	downwidget()->update();

	QPushButton *m_btnlow = new QPushButton("经典版电脑清理", this->downwidget());
	QPushButton *m_btnlow1 = new QPushButton("微信清理", this->downwidget());
	QPushButton *m_btnlow2 = new QPushButton("苹果设备清理", this->downwidget());
	QPushButton *m_btnlow3 = new QPushButton("系统盘瘦身", this->downwidget());

	QPushButton *m_btnlow4 = new QPushButton("查找大文件", this->downwidget());
	QPushButton *m_btnlow5 = new QPushButton("自动清理", this->downwidget());
	QPushButton *m_btnlow6 = new QPushButton("恢复区", this->downwidget());

	m_btnlow->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow1->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow2->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");

	m_btnlow3->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow4->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow5->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");
	m_btnlow6->setStyleSheet("QPushButton::hover{color:rgb(36,147,229,180)}"
		"QPushButton{background:transparent;color: rgb(36,147,229)}");

	m_btnlow->setGeometry(15, 422, 100, 20);
	m_btnlow1->setGeometry(440, 422, 100, 20);
	m_btnlow2->setGeometry(515, 422, 100, 20);
	m_btnlow3->setGeometry(610, 422, 100, 20);
	m_btnlow4->setGeometry(690, 422, 100, 20);
	m_btnlow5->setGeometry(765, 422, 100, 20);
	m_btnlow6->setGeometry(825, 422, 100, 20);

	m_btnlow->setCursor(Qt::PointingHandCursor);
	m_btnlow1->setCursor(Qt::PointingHandCursor);
	m_btnlow2->setCursor(Qt::PointingHandCursor);
	m_btnlow3->setCursor(Qt::PointingHandCursor);
	m_btnlow4->setCursor(Qt::PointingHandCursor);
	m_btnlow5->setCursor(Qt::PointingHandCursor);
	m_btnlow6->setCursor(Qt::PointingHandCursor);



	m_btnlow->adjustSize();
	m_btnlow1->adjustSize();
	m_btnlow2->adjustSize();
	m_btnlow3->adjustSize();
	m_btnlow4->adjustSize();
	m_btnlow5->adjustSize();
	m_btnlow6->adjustSize();


	cleanMainButton *m_btn = new cleanMainButton(":/image/clean/clean_trash_check.png", ":/image/clean/clean_trash_uncheck.png"
		, ":/image/clean/clean_trash_anim.png", ":/image/clean/clean_trash_anim_gray.png", 13, downwidget());
	m_btn->setGeometry(130, 60, 90, 90);

	cleanMainButton *m_btn1 = new cleanMainButton(":/image/clean/clean_trace_check.png", ":/image/clean/clean_trace_uncheck.png"
		, ":/image/clean/clean_trace_anim.png", ":/image/clean/clean_trace_anim_gray.png", 17, downwidget());
	m_btn1->setGeometry(410, 60, 90, 90);

	cleanMainButton *m_btn2 = new cleanMainButton(":/image/clean/clean_reg_check.png", ":/image/clean/clean_reg_uncheck.png"
		, ":/image/clean/clean_reg_anim.png", ":/image/clean/clean_reg_anim_gray.png", 17, downwidget());
	m_btn2->setGeometry(670, 60, 90, 90);

	cleanMainButton *m_btn3 = new cleanMainButton(":/image/clean/clean_plugin_check.png", ":/image/clean/clean_plugin_uncheck.png"
		, ":/image/clean/clean_plugin_anim.png", ":/image/clean/clean_plugin_anim_gray.png", 17, downwidget());
	m_btn3->setGeometry(130, 230, 90, 90);

	cleanMainButton *m_btn4 = new cleanMainButton(":/image/clean/clean_soft_check.png", ":/image/clean/clean_soft_uncheck.png"
		, ":/image/clean/clean_soft_anim.png", ":/image/clean/clean_soft_anim_gray.png", 17, downwidget());
	m_btn4->setGeometry(410, 230, 90, 90);

	cleanMainButton *m_btn5 = new cleanMainButton(":/image/clean/clean_cookies_check.png", ":/image/clean/clean_cookies_uncheck.png"
		, ":/image/clean/clean_cookies_anim.png", ":/image/clean/clean_cookies_anim_gray.png", 20, downwidget());
	m_btn5->setGeometry(670, 230, 90, 90);




	QFont font;
	font.setFamily("宋体");
	font.setBold(true);
	font.setPixelSize(16);
	QLabel *m_labqllj = new QLabel("清理垃圾", this->downwidget());
	QLabel *m_labqlhj = new QLabel("清理痕迹", this->downwidget());
	QLabel *m_labqlzcb = new QLabel("清理注册表", this->downwidget());
	QLabel *m_labqlcj = new QLabel("清理插件", this->downwidget());
	QLabel *m_labqlrj = new QLabel("清理软件", this->downwidget());
	QLabel *m_labqlcookies = new QLabel("清理Cookies", this->downwidget());


	m_labqllj->setStyleSheet("color:rgb(102,102,102);");
	m_labqlhj->setStyleSheet("color:rgb(102,102,102);");
	m_labqlzcb->setStyleSheet("color:rgb(102,102,102);");
	m_labqlcj->setStyleSheet("color:rgb(102,102,102);");
	m_labqlrj->setStyleSheet("color:rgb(102,102,102);");
	m_labqlcookies->setStyleSheet("color:rgb(102,102,102);");


	m_labqllj->setFont(font);
	m_labqlhj->setFont(font);
	m_labqlzcb->setFont(font);
	m_labqlcj->setFont(font);
	m_labqlrj->setFont(font);
	m_labqlcookies->setFont(font);

	m_labqllj->setGeometry(140, 150, 110, 60);
	m_labqlhj->setGeometry(420, 150, 110, 60);
	m_labqlzcb->setGeometry(675, 150, 110, 60);
	m_labqlcj->setGeometry(140, 320, 110, 60);
	m_labqlrj->setGeometry(420, 320, 110, 60);
	m_labqlcookies->setGeometry(675, 320, 110, 60);



	m_labqllj->adjustSize();
	m_labqlhj->adjustSize();
	m_labqlzcb->adjustSize();
	m_labqlcj->adjustSize();
	m_labqlrj->adjustSize();
	m_labqlcookies->adjustSize();

	QLabel *m_lab0 = new QLabel("清理电脑中的垃圾文件", this->downwidget());
	QLabel *m_lab1 = new QLabel("清理浏览器使用痕迹", this->downwidget());
	QLabel *m_lab2 = new QLabel("清理无效的注册表项目", this->downwidget());
	QLabel *m_lab3 = new QLabel("清理无用的插件,降低打扰", this->downwidget());
	QLabel *m_lab4 = new QLabel("清理推广,弹窗不常用的软件", this->downwidget());
	QLabel *m_lab5 = new QLabel("清理上网,游戏,购物等记录", this->downwidget());


	m_lab0->setStyleSheet("color:rgb(124,124,124);");
	m_lab1->setStyleSheet("color:rgb(124,124,124);");
	m_lab2->setStyleSheet("color:rgb(124,124,124);");
	m_lab3->setStyleSheet("color:rgb(124,124,124);");
	m_lab4->setStyleSheet("color:rgb(124,124,124);");
	m_lab5->setStyleSheet("color:rgb(124,124,124);");

	m_lab0->setGeometry(115, 175, 150, 60);
	m_lab1->setGeometry(400, 175, 150, 60);
	m_lab2->setGeometry(655, 175, 150, 60);
	m_lab3->setGeometry(100, 345, 150, 60);
	m_lab4->setGeometry(385, 345, 150, 60);
	m_lab5->setGeometry(650, 345, 150, 60);

	m_lab0->adjustSize();
	m_lab1->adjustSize();
	m_lab2->adjustSize();
	m_lab3->adjustSize();
	m_lab4->adjustSize();
	m_lab5->adjustSize();




}
void dnqlWidget::paintEvent(QPaintEvent *)
{

	//dnqlWidget::paintEvent(e);

}
