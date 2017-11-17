#pragma once

#include <QtWidgets/QWidget>
#include "ui_XTreeView.h"

class XTreeView : public QWidget
{
	Q_OBJECT

public:
	XTreeView(QWidget *parent = Q_NULLPTR);

private:
	Ui::XTreeViewClass ui;
};
