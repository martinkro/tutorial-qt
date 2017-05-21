#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QImage>
#include <QRect>

class Paddle {

public:
	Paddle();
	~Paddle();

public:
	void resetState();
	void move();
	void setDx(int);
	QRect getRect();
	QImage & getImage();

private:
	QImage image;
	QRect rect;
	int dx;
	static const int INITIAL_X = 200;
	static const int INITIAL_Y = 360;
};

class Brick {

public:
	Brick(int, int);
	~Brick();

public:
	bool isDestroyed();
	void setDestroyed(bool);
	QRect getRect();
	void setRect(QRect);
	QImage & getImage();

private:
	QImage image;
	QRect rect;
	bool destroyed;
};

class Ball {

public:
	Ball();
	~Ball();

public:
	void resetState();
	void autoMove();
	void setXDir(int);
	void setYDir(int);
	int getXDir();
	int getYDir();
	QRect getRect();
	QImage & getImage();

private:
	int xdir;
	int ydir;
	QImage image;
	QRect rect;
	static const int INITIAL_X = 230;
	static const int INITIAL_Y = 355;
	static const int RIGHT_EDGE = 300;
};

class Breakout : public QWidget {

public:
	Breakout(QWidget *parent = 0);
	~Breakout();

protected:
	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);
	void keyPressEvent(QKeyEvent *);
	void keyReleaseEvent(QKeyEvent *);
	void drawObjects(QPainter *);
	void finishGame(QPainter *, QString);
	void moveObjects();

	void startGame();
	void pauseGame();
	void stopGame();
	void victory();
	void checkCollision();

private:
	int x;
	int timerId;
	static const int N_OF_BRICKS = 30;
	static const int DELAY = 10;
	static const int BOTTOM_EDGE = 400;
	Ball *ball;
	Paddle *paddle;
	Brick *bricks[N_OF_BRICKS];
	bool gameOver;
	bool gameWon;
	bool gameStarted;
	bool paused;
};