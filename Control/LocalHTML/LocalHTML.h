#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LocalHTML.h"

class LocalHTML : public QMainWindow
{
	Q_OBJECT

public:
	LocalHTML(QWidget *parent = Q_NULLPTR);

private:
	Ui::LocalHTMLClass ui;
};
