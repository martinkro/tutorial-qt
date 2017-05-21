#pragma once

#include <QMainWindow>

class ToolBar : public QMainWindow
{
	Q_OBJECT

public:
	ToolBar(QWidget *parent = 0);
	~ToolBar();
};
