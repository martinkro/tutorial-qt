#pragma once

#include <QtWidgets/QWidget>
#include "ui_lineedit.h"
#include <qlineedit.h>
class LineEdit : public QWidget
{
	Q_OBJECT

public:
	LineEdit(QWidget *parent = Q_NULLPTR);
	public slots:
	void onEmailChoosed(const QString&);

private:
	Ui::LineEditClass ui;
	QLineEdit* email;
};
