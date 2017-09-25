#ifndef LOGIN_QRCODE_H
#define LOGIN_QRCODE_H

#include "loginbase.h"

class LoginQRCode:public LoginBase
{
    Q_OBJECT
public:
    explicit LoginQRCode(QWidget* parent = Q_NULLPTR);
    virtual ~LoginQRCode(){}
};


#endif