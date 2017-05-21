#pragma once

#include <QWidget>

class TestPainting : public QWidget
{
	Q_OBJECT

public:
	TestPainting(QWidget *parent);
	~TestPainting();
};

class Lines : public QWidget {

public:
	Lines(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *event);
	void drawLines(QPainter *qp);
};

class Colours : public QWidget {

public:
	Colours(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);

private:
	void doPainting();
};

class Patterns : public QWidget {

public:
	Patterns(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);

private:
	void doPainting();
};

class TransparentRectangles : public QWidget {

public:
	TransparentRectangles(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *event);
	void doPainting();
};

class Donut : public QWidget {

public:
	Donut(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);

private:
	void doPainting();
};


class Shapes : public QWidget {

public:
	Shapes(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);

private:
	void doPainting();
};

class LinearGradients : public QWidget {

public:
	LinearGradients(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);

private:
	void doPainting();
};

class RadialGradient : public QWidget {

public:
	RadialGradient(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);

private:
	void doPainting();
};

class Puff : public QWidget {

public:
	Puff(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);

private:
	int x;
	qreal opacity;
	int timerId;

	void doPainting();
};
