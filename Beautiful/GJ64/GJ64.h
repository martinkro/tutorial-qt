#pragma once

#include <QtWidgets/QWidget>
#include "ui_GJ64.h"

class GJ64 : public QWidget
{
	Q_OBJECT

public:
	GJ64(QWidget *parent = Q_NULLPTR);

private:
	Ui::GJ64Class ui;
};
