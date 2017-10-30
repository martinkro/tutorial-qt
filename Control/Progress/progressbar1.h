#pragma once

#include <QWidget>
#include <QPaintEvent>
class ProgressBar1 : public QWidget
{
	Q_OBJECT

public:
	ProgressBar1(QWidget *parent = Q_NULLPTR);
	~ProgressBar1();

signals:

public slots :
		void setProgress(int val);

protected:
	void paintEvent(QPaintEvent *);

private:
	double progress;
};
