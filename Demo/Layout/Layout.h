#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Layout.h"

class Layout : public QMainWindow
{
	Q_OBJECT

public:
	Layout(QWidget *parent = Q_NULLPTR);

private:
	Ui::LayoutClass ui;
};

class Layouts : public QWidget {

public:
	Layouts(QWidget *parent = 0);
};

class FormEx : public QWidget {

public:
	FormEx(QWidget *parent = 0);
};

class Calculator : public QWidget {

public:
	Calculator(QWidget *parent = 0);

};

class Review : public QWidget {

public:
	Review(QWidget *parent = 0);
};
