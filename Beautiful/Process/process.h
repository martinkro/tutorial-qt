#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_process.h"

class Process : public QMainWindow
{
	Q_OBJECT

public:
	Process(QWidget *parent = Q_NULLPTR);

private:
	Ui::ProcessClass ui;
};
