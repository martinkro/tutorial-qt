#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class TestEvents : public QObject
{
	Q_OBJECT

public:
	TestEvents(QObject *parent);
	~TestEvents();
};

class Click : public QWidget {

public:
	Click(QWidget *parent = 0);
};

class KeyPress : public QWidget {

public:
	KeyPress(QWidget *parent = 0);

protected:
	void keyPressEvent(QKeyEvent * e);
};

class Move : public QWidget {

	Q_OBJECT

public:
	Move(QWidget *parent = 0);

protected:
	void moveEvent(QMoveEvent *e);
};

class Disconnect : public QWidget {

	Q_OBJECT

public:
	Disconnect(QWidget *parent = 0);

	private slots:
	void onClick();
	void onCheck(int);

private:
	QPushButton *clickBtn;
};

class Timer : public QWidget {

public:
	Timer(QWidget *parent = 0);

protected:
	void timerEvent(QTimerEvent *e);

private:
	QLabel *label;
};
