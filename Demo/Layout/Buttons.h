#pragma once

#include <QWidget>
#include <QPushButton>

class Buttons : public QWidget
{
	Q_OBJECT

public:
	Buttons(QWidget *parent = 0);
	~Buttons();

private:
	QPushButton *okBtn;
	QPushButton *applyBtn;
};
