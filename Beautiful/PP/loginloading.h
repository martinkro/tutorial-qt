#ifndef LOGIN_LOADING_H
#define LOGIN_LOADING_H

#include "loginbase.h"

class LoginLoading:public LoginBase
{
    Q_OBJECT
public:
    explicit LoginLoading(QWidget* parent = Q_NULLPTR);
    virtual ~LoginLoading(){}
};

#endif