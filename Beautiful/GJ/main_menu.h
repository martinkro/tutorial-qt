#pragma once

#include <QMenu>

class MainMenu : public QMenu
{
	Q_OBJECT

public:

	explicit MainMenu(QWidget *parent = 0);

	void translateActions();

signals:

	void showSettingDialog();
	void showNewCharacter();
	void showAboutUs();

private:

	void createActions();

private:

	QAction *action_setting; //设置
	QAction *action_new_character; //新版特性
	QAction *action_check_update; //检查更新
	QAction *action_change_company; //切换为企业版
	QAction *action_help_online; //在线帮助
	QAction *action_platform_help; //论坛求助
	QAction *action_login_home; //360网站
	QAction *action_protect; //隐私保护
	QAction *action_about_us; //关于我们
};
