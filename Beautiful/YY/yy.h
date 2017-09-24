#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_yy.h"

class YY : public QMainWindow
{
	Q_OBJECT

public:
	YY(QWidget *parent = Q_NULLPTR);

private:
	Ui::YYClass ui;
};
