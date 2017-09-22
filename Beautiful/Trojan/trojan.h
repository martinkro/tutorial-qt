#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_trojan.h"

class Trojan : public QMainWindow
{
	Q_OBJECT

public:
	Trojan(QWidget *parent = Q_NULLPTR);

private:
	Ui::TrojanClass ui;
};
