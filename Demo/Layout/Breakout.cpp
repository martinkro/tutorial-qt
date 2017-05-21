#include <QPainter>
#include <QApplication>

#include <iostream>
#include "Breakout.h"

Paddle::Paddle() {

	dx = 0;
	image.load("paddle.png");

	rect = image.rect();
	resetState();
}

Paddle::~Paddle() {

	std::cout << ("Paddle deleted") << std::endl;
}

void Paddle::setDx(int x) {
	dx = x;
}

void Paddle::move() {

	int x = rect.x() + dx;
	int y = rect.top();

	rect.moveTo(x, y);
}

void Paddle::resetState() {

	rect.moveTo(INITIAL_X, INITIAL_Y);
}

QRect Paddle::getRect() {

	return rect;
}

QImage & Paddle::getImage() {

	return image;
}
Brick::Brick(int x, int y) {

	image.load("brickie.png");
	destroyed = false;
	rect = image.rect();
	rect.translate(x, y);
}

Brick::~Brick() {

	std::cout << ("Brick deleted") << std::endl;
}

QRect Brick::getRect() {

	return rect;
}

void Brick::setRect(QRect rct) {

	rect = rct;
}

QImage & Brick::getImage() {

	return image;
}

bool Brick::isDestroyed() {

	return destroyed;
}

void Brick::setDestroyed(bool destr) {

	destroyed = destr;
}

Ball::Ball() {

	xdir = 1;
	ydir = -1;

	image.load("ball.png");

	rect = image.rect();
	resetState();
}

Ball::~Ball() {

	std::cout << ("Ball deleted") << std::endl;
}

void Ball::autoMove() {

	rect.translate(xdir, ydir);

	if (rect.left() == 0) {
		xdir = 1;
	}

	if (rect.right() == RIGHT_EDGE) {
		xdir = -1;
	}

	if (rect.top() == 0) {
		ydir = 1;
	}
}

void Ball::resetState() {

	rect.moveTo(INITIAL_X, INITIAL_Y);
}

void Ball::setXDir(int x) {

	xdir = x;
}

void Ball::setYDir(int y) {

	ydir = y;
}

int Ball::getXDir() {

	return xdir;
}

int Ball::getYDir() {

	return ydir;
}

QRect Ball::getRect() {

	return rect;
}

QImage & Ball::getImage() {

	return image;
}

Breakout::Breakout(QWidget *parent)
	: QWidget(parent) {

	x = 0;
	gameOver = false;
	gameWon = false;
	paused = false;
	gameStarted = false;
	ball = new Ball();
	paddle = new Paddle();

	int k = 0;

	for (int i = 0; i<5; i++) {
		for (int j = 0; j<6; j++) {
			bricks[k] = new Brick(j * 40 + 30, i * 10 + 50);
			k++;
		}
	}
}

Breakout::~Breakout() {

	delete ball;
	delete paddle;

	for (int i = 0; i<N_OF_BRICKS; i++) {
		delete bricks[i];
	}
}

void Breakout::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	QPainter painter(this);

	if (gameOver) {

		finishGame(&painter, "Game lost");

	}
	else if (gameWon) {

		finishGame(&painter, "Victory");
	}
	else {

		drawObjects(&painter);
	}
}

void Breakout::finishGame(QPainter *painter, QString message) {

	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.width(message);

	painter->setFont(font);
	int h = height();
	int w = width();

	painter->translate(QPoint(w / 2, h / 2));
	painter->drawText(-textWidth / 2, 0, message);
}

void Breakout::drawObjects(QPainter *painter) {

	painter->drawImage(ball->getRect(), ball->getImage());
	painter->drawImage(paddle->getRect(), paddle->getImage());

	for (int i = 0; i<N_OF_BRICKS; i++) {
		if (!bricks[i]->isDestroyed()) {
			painter->drawImage(bricks[i]->getRect(), bricks[i]->getImage());
		}
	}
}

void Breakout::timerEvent(QTimerEvent *e) {

	Q_UNUSED(e);

	moveObjects();
	checkCollision();
	repaint();
}

void Breakout::moveObjects() {

	ball->autoMove();
	paddle->move();
}

void Breakout::keyReleaseEvent(QKeyEvent *e) {

	int dx = 0;

	switch (e->key()) {
	case Qt::Key_Left:
		dx = 0;
		paddle->setDx(dx);
		break;

	case Qt::Key_Right:
		dx = 0;
		paddle->setDx(dx);
		break;
	}
}

void Breakout::keyPressEvent(QKeyEvent *e) {

	int dx = 0;

	switch (e->key()) {
	case Qt::Key_Left:

		dx = -1;
		paddle->setDx(dx);

		break;

	case Qt::Key_Right:

		dx = 1;
		paddle->setDx(dx);
		break;

	case Qt::Key_P:

		pauseGame();
		break;

	case Qt::Key_Space:

		startGame();
		break;

	case Qt::Key_Escape:

		qApp->exit();
		break;

	default:
		QWidget::keyPressEvent(e);
	}
}

void Breakout::startGame() {

	if (!gameStarted) {
		ball->resetState();
		paddle->resetState();

		for (int i = 0; i<N_OF_BRICKS; i++) {
			bricks[i]->setDestroyed(false);
		}

		gameOver = false;
		gameWon = false;
		gameStarted = true;
		timerId = startTimer(DELAY);
	}
}

void Breakout::pauseGame() {

	if (paused) {

		timerId = startTimer(DELAY);
		paused = false;
	}
	else {

		paused = true;
		killTimer(timerId);
	}
}

void Breakout::stopGame() {

	killTimer(timerId);
	gameOver = true;
	gameStarted = false;
}

void Breakout::victory() {

	killTimer(timerId);
	gameWon = true;
	gameStarted = false;
}

void Breakout::checkCollision() {

	if (ball->getRect().bottom() > BOTTOM_EDGE) {
		stopGame();
	}

	for (int i = 0, j = 0; i<N_OF_BRICKS; i++) {

		if (bricks[i]->isDestroyed()) {
			j++;
		}

		if (j == N_OF_BRICKS) {
			victory();
		}
	}

	if ((ball->getRect()).intersects(paddle->getRect())) {

		int paddleLPos = paddle->getRect().left();
		int ballLPos = ball->getRect().left();

		int first = paddleLPos + 8;
		int second = paddleLPos + 16;
		int third = paddleLPos + 24;
		int fourth = paddleLPos + 32;

		if (ballLPos < first) {
			ball->setXDir(-1);
			ball->setYDir(-1);
		}

		if (ballLPos >= first && ballLPos < second) {
			ball->setXDir(-1);
			ball->setYDir(-1 * ball->getYDir());
		}

		if (ballLPos >= second && ballLPos < third) {
			ball->setXDir(0);
			ball->setYDir(-1);
		}

		if (ballLPos >= third && ballLPos < fourth) {
			ball->setXDir(1);
			ball->setYDir(-1 * ball->getYDir());
		}

		if (ballLPos > fourth) {
			ball->setXDir(1);
			ball->setYDir(-1);
		}
	}

	for (int i = 0; i<N_OF_BRICKS; i++) {

		if ((ball->getRect()).intersects(bricks[i]->getRect())) {

			int ballLeft = ball->getRect().left();
			int ballHeight = ball->getRect().height();
			int ballWidth = ball->getRect().width();
			int ballTop = ball->getRect().top();

			QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
			QPoint pointLeft(ballLeft - 1, ballTop);
			QPoint pointTop(ballLeft, ballTop - 1);
			QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

			if (!bricks[i]->isDestroyed()) {
				if (bricks[i]->getRect().contains(pointRight)) {
					ball->setXDir(-1);
				}

				else if (bricks[i]->getRect().contains(pointLeft)) {
					ball->setXDir(1);
				}

				if (bricks[i]->getRect().contains(pointTop)) {
					ball->setYDir(1);
				}

				else if (bricks[i]->getRect().contains(pointBottom)) {
					ball->setYDir(-1);
				}

				bricks[i]->setDestroyed(true);
			}
		}
	}
}

