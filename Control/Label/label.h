#pragma once

#include <QtWidgets/QWidget>
#include "ui_label.h"

class Label : public QWidget
{
	Q_OBJECT

public:
	Label(QWidget *parent = Q_NULLPTR);

private:
	Ui::LabelClass ui;
};
