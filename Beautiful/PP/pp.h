#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_pp.h"

class PP : public QMainWindow
{
	Q_OBJECT

public:
	PP(QWidget *parent = Q_NULLPTR);

private:
	Ui::PPClass ui;
};
