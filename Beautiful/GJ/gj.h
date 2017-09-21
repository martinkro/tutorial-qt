#pragma once

#include <QtWidgets/QWidget>
#include "ui_gj.h"

class GJ : public QWidget
{
	Q_OBJECT

public:
	GJ(QWidget *parent = Q_NULLPTR);

private:
	Ui::GJClass ui;
};
