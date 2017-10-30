#pragma once

#include <QtWidgets/QWidget>
#include "ui_button2.h"

#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QCheckBox>
#include <QRadioButton>



class Button2 : public QWidget
{
	Q_OBJECT

public:
	Button2(QWidget *parent = Q_NULLPTR);

	//Q_PROPERTY(int width READ getWidth WRITE setWidth);

	//int getWidth() { return width; }
	//void setWidth(int w) { width = w; }

private:
	Ui::Button2Class ui;
	QPushButton* m_pushbutton;
	QToolButton* m_toolbutton;
	QToolBar* m_toolbar;

	//int width;

};
