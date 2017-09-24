#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qqlogin.h"

class QQLogin : public QMainWindow
{
	Q_OBJECT

public:
	QQLogin(QWidget *parent = Q_NULLPTR);

private:
	Ui::QQLoginClass ui;
};
