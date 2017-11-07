#pragma once

#include <QtWidgets/QWidget>
#include "ui_mv.h"

class MV : public QWidget
{
	Q_OBJECT

public:
	MV(QWidget *parent = Q_NULLPTR);

private:
	Ui::MVClass ui;
};
