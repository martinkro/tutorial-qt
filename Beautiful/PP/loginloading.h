#ifndef LOGIN_LOADING_H
#define LOGIN_LOADING_H

#include "loginbase.h"
#include "customcontrol/xprogressindicator.h"
#include <QTimer>

class LoginLoading:public LoginBase
{
    Q_OBJECT
public:
    explicit LoginLoading(QWidget* parent = Q_NULLPTR);
    virtual ~LoginLoading(){}

	void start();
	void stop();

signals:
	void login_success();
	void login_fail();

private:
	void loginTimeout();

private:
	XProgressIndicatorTimer* m_progress;
	QTimer* m_timer;
};

#endif