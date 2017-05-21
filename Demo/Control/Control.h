#ifndef CONTROL_H
#define CONTROL_H

#include <QtWidgets/QMainWindow>
#include "ui_Control.h"

class Control : public QMainWindow
{
	Q_OBJECT

public:
	Control(QWidget *parent = Q_NULLPTR);

private:
	Ui::ControlClass ui;
};

#endif
