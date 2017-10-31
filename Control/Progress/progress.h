#pragma once

#include <QtWidgets/QWidget>
#include <QSlider>
#include "ui_progress.h"

#include "progressbar1.h"
#include "progressbar2.h"
#include "QRoundProgressBar.h"

class Progress : public QWidget
{
	Q_OBJECT

public:
	Progress(QWidget *parent = Q_NULLPTR);

private:
	void connectToSlider(QRoundProgressBar* bar, QSlider* slider);
	Ui::ProgressClass ui;
	ProgressBar1* m_progressbar1;
	ProgressBar2* m_progressbar2;
};
