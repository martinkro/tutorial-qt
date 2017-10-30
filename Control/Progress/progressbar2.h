#pragma once

#include <QWidget>

class ProgressBar2 : public QWidget
{
	Q_OBJECT

public:
	ProgressBar2(QWidget *parent = Q_NULLPTR);
	~ProgressBar2();

	void upd(qreal pp) {
		if (p == pp) return;
		p = pp;
		update();
	}

protected:
	void paintEvent(QPaintEvent *);

	qreal p;
};
