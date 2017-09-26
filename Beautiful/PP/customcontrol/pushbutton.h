#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <QPushButton>
#include <QPaintEvent>
#include <QMouseEvent>

class PushButton:public QPushButton
{
	Q_OBJECT
public:
	explicit PushButton(QWidget *parent = Q_NULLPTR);
	explicit PushButton(const QString& text, QWidget* parent = Q_NULLPTR);
	virtual ~PushButton(){}
	enum BUTTON_STATUS{NORMAL, PRESSED, HOVER};

	void setButtonBackground(const QString& path);


protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

private:
	BUTTON_STATUS m_status;  // record the status to take different painting action
	bool m_isPressed;   	 // whether the button is pressed.
	QString m_imagePath;
};


#endif