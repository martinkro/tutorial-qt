#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Sample.h"

class Sample : public QMainWindow
{
	Q_OBJECT

public:
	Sample(QWidget *parent = Q_NULLPTR);

private:
	Ui::SampleClass ui;
};
