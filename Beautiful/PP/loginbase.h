#ifndef LOGIN_BASE_H
#define LOGIN_BASE_H

#include <QWidget>

class LoginBase:public QWidget
{
    Q_OBJECT
public:
    explicit LoginBase(QWidget* parent = Q_NULLPTR);
    virtual ~LoginBase(){}
};


#endif