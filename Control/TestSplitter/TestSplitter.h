#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestSplitter.h"

class TestSplitter : public QWidget
{
	Q_OBJECT

public:
	TestSplitter(QWidget *parent = Q_NULLPTR);

private:
	Ui::TestSplitterClass ui;
};
