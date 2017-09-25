#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "customcontrol/xbasewindow.h"

class LoginWindow:public XBaseWindow
{
    Q_OBJECT
    public:
    explicit LoginWindow(QWidget* parent = Q_NULLPTR);
    virtual ~LoginWindow(){}
};

#endif