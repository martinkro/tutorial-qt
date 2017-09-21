#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GJ10.h"

class GJ10 : public QMainWindow
{
	Q_OBJECT

public:
	GJ10(QWidget *parent = Q_NULLPTR);

private:
	Ui::GJ10Class ui;
};
