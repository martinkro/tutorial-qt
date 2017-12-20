#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiThread.h"
#include "NumberThread.h"

class QLineEdit;
class QPushButton;

class MultiThread : public QMainWindow
{
	Q_OBJECT

public:
	MultiThread(QWidget *parent = Q_NULLPTR);

public slots:
	void onValueChanged(int value);
	void onStartClicked();
	void onStopClicked();

private:
	// Ui::MultiThreadClass ui;
	QPushButton* btnStart;
	QPushButton* btnStop;
	QLineEdit* editNumber;

	NumberThread threadNumber;
};
