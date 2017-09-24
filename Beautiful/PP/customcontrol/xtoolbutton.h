#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QLinearGradient>
#include <QPalette>

class XToolButton : public QToolButton
{
	Q_OBJECT

public:
	XToolButton(const QString& path, QWidget *parent = NULL);
	~XToolButton(){}
	void setButtonPressed(bool isPressed);


protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void doPaintStuff(int topColor, int centerColor, int bottomColor);
private:
	bool m_mousePressed;
	bool m_mouseHover;
	QString m_filePath;
};

#endif