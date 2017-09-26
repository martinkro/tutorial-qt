#ifndef LOGIN_TITLE_BAR_H
#define LOGIN_TITLE_BAR_H

#include "customcontrol/pushbutton.h"

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QList>

class LoginTitleBar:public QWidget
{
	Q_OBJECT
public:
	explicit LoginTitleBar(QWidget *parent = Q_NULLPTR);
	virtual ~LoginTitleBar(){}

private:
	void initUI();
	void initConnect();


signals:
	void buttonMinimizedClicked();
	void buttonCloseClicked();
private:
	// top part
	QLabel* m_labelTitle;
	
	PushButton* m_buttonMinimized;
	PushButton* m_buttonClose;
	
	QHBoxLayout* m_layoutMain;

};

#endif