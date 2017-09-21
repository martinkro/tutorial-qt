#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>
#include "title_widget.h"
#include "content_widget.h"
#include "system_tray.h"
#include "about_us.h"
#include "main_menu.h"
#include "character_widget.h"
#include "setting_dialog.h"
#include "skin_widget.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:

	MainWidget(QWidget *parent = 0);
	~MainWidget();

protected:

	void paintEvent(QPaintEvent *);

	public slots:

	void showWidget();

	private slots:

	void showMax();
	void showSkinWidget();
	void showMainMenu();
	void showSettingDialog();
	void showAboutUs();
	void showNewCharacter();
	void changeSkin(QString skin_name);
	void iconIsActived(QSystemTrayIcon::ActivationReason reason);

private:

	QRect location;
	TitleWidget *title_widget; //������
	ContentWidget *content_widget; //����������
	SystemTray *system_tray; //������
	SettingDialog *setting_dialog; //���ý���
	CharacterWidget *character_widget; //�°����Խ���
	AboutUsDialog *about_us_dialog; //�������ǽ���
	QString skin_name;//�����ڱ���ͼƬ������
	MainMenu *main_menu; //���˵�
	SkinWidget *skin_widget; //��ʾƤ������

};

#endif // MAINWIDGET_H
