#ifndef LOGIN_QRCODE_H
#define LOGIN_QRCODE_H

#include "loginbase.h"
#include "customcontrol/pushbutton.h"
#include <QPaintEvent>
#include <QLabel>
#include <QVBoxLayout>

class LoginQRCode:public LoginBase
{
    Q_OBJECT
public:
    explicit LoginQRCode(QWidget* parent = Q_NULLPTR);
    virtual ~LoginQRCode(){}

protected:
	void paintEvent(QPaintEvent* event);

signals:
	void cancel_clicked();

private:
	void initUI();
	void initConnect();

private:
	QLabel* m_labelInfo;
	QLabel* m_labelQRCode;
	PushButton* m_buttonCancel;  // ·µ»Ø
	QVBoxLayout* m_layoutMain;
};


#endif