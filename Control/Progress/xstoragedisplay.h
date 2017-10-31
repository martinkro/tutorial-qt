#pragma once

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>

class XStorageDisplay : public QWidget
{
	Q_OBJECT

public:
	XStorageDisplay(QWidget *parent = Q_NULLPTR);
	~XStorageDisplay();

public:
	void setUsedValue(int value);
	//void setSize(int width, int height);  
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent * event);
	//void mousePressEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
	void showEvent(QShowEvent *event);
	void hideEvent(QHideEvent *event);

	private slots:
	void slotUpdateTimer();

private:
	QPoint beginDrag;
	bool bPressFlag;

	QPixmap backGround;
	int userdVaule;
	int currentValue;
	QLabel *startValueLabel;
	QLabel *endValueLabel;
	QLabel *dispayValueLabel;

	QTimer *updateTimer;
};
