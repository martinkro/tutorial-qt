#pragma once

#include <QtWidgets/QWidget>
#include "ui_progress.h"

#include "progressbar1.h"
#include "progressbar2.h"

class Progress : public QWidget
{
	Q_OBJECT

public:
	Progress(QWidget *parent = Q_NULLPTR);

private:
	Ui::ProgressClass ui;
	ProgressBar1* m_progressbar1;
	ProgressBar2* m_progressbar2;
};
