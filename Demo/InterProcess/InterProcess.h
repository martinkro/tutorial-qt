#pragma once

#include <QtWidgets/QWidget>
//#include "ui_InterProcess.h"

class QPushButton;
class InterProcess : public QWidget
{
	Q_OBJECT

public:
	InterProcess(QWidget *parent = Q_NULLPTR);

public slots:
	void wrapperDone(const QString&);
	void wrapperFinished();

private:
	//Ui::InterProcessClass ui;
private:
	QPushButton* btnTestMyLibrary;
};
