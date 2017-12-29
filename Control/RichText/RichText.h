#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RichText.h"

class RichText : public QMainWindow
{
	Q_OBJECT

public:
	RichText(QWidget *parent = Q_NULLPTR);

	QString getHelpInfo();

private:
	Ui::RichTextClass ui;
};
