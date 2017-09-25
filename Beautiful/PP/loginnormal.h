#ifndef LOGIN_NORMAL_H
#define LOGIN_NORMAL_H

#include "loginbase.h"

class LoginNormal:public LoginBase
{
    Q_OBJECT
public:
    explicit LoginNormal(QWidget* parent = Q_NULLPTR);
    virtual ~LoginNormal(){}
};

#endif