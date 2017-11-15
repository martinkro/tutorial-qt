#pragma once

#include <QtWidgets/QWidget>
#include "ui_Scroll.h"

class Scroll : public QWidget
{
	Q_OBJECT

public:
	Scroll(QWidget *parent = Q_NULLPTR);

private:
	Ui::ScrollClass ui;
};
