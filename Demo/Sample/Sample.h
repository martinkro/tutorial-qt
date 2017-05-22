#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include "ui_Sample.h"

class Sample : public QMainWindow
{
	Q_OBJECT

public:
	Sample(QWidget *parent = Q_NULLPTR);

private:
	Ui::SampleClass ui;
};

class MainWindow :public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = Q_NULLPTR);

private:
	void initUI();
	QLabel* label;
private slots:
	void openFileDialog();
	void openDirDialog();
};
