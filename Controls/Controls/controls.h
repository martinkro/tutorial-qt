#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_controls.h"

class Controls : public QMainWindow
{
	Q_OBJECT

public:
	Controls(QWidget *parent = Q_NULLPTR);

private:
	Ui::ControlsClass ui;
};
