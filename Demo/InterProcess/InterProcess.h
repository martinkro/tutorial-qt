#pragma once

#include <QtWidgets/QWidget>
//#include "ui_InterProcess.h"

class InterProcess : public QWidget
{
	Q_OBJECT

public:
	InterProcess(QWidget *parent = Q_NULLPTR);

public slots:
	void wrapperDone(const QString&);

private:
	//Ui::InterProcessClass ui;
};
