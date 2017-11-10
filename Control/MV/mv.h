#pragma once

#include <QtWidgets/QWidget>
#include "ui_mv.h"

class MV : public QWidget
{
	Q_OBJECT

public:
	MV(QWidget *parent = Q_NULLPTR);

private:
	void testQStringListModel();
	void testQFileSystemModel();
	void testSpinBoxDelegate();
	void testQTableView();
	void testQProgressBar();
	void testProgressBarDelegate();
	void testQListViewWidget();

private:
	Ui::MVClass ui;
};
