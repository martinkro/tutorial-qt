#ifndef LOGIN_NORMAL_H
#define LOGIN_NORMAL_H

#include "loginbase.h"
#include "customcontrol/pushbutton.h"
#include <QLineEdit>

class LoginNormal:public LoginBase
{
    Q_OBJECT
public:
    explicit LoginNormal(QWidget* parent = Q_NULLPTR);
    virtual ~LoginNormal(){}

signals:
	void login_clicked();
	void qrcode_clicked();
private:
	void initUI();
	void initConnect();

private:
	QLineEdit* m_lineeditUsername;
	QLineEdit* m_lineeditPassword;

	QString m_initUsernameText;
	QString m_initPasswordText;

	PushButton* m_buttonLogin;
	PushButton* m_buttonQRCode;
};

#endif