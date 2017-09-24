/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#ifndef LOGIN_H
#define LOGIN_H

//#define _HH_DEBUG_


#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include "login/softkeyboard/softkeyboard.h"
#include "connect/hhnet.h"
#include "login/loginpanel/verifyimgframe.h"
#include <QMovie>
#include <QPropertyAnimation>
#include <QLabel>




namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void changeEvent(QEvent *event);    //窗口状态变化
    void mousePressEvent(QMouseEvent *event);   //鼠标按下
    void mouseMoveEvent(QMouseEvent *event);    //鼠标移动
    bool eventFilter(QObject *obj, QEvent *event);    //事件过滤

signals:
    void loginMainWidget(QString name);
    
private slots:
    void on_keyboard_clicked(bool checked);  //软键盘点击
    void softkeyboardinput(QString str);    //软键盘有输入

    void on_button_login_clicked();    //登录按钮点击
    void on_switch_single_clicked(bool checked);  //多用户登陆按钮

    void checkVerifycodeFinished(bool getCode,QString code);
    void verifyCodeEditFinished(bool getVerify, QString verify);
    void loginFinished(bool loginok, QString message);
    void loginErrorInf(int id, QString message);
    void clickOk();

private:
    Ui::Login *ui;
    QPoint  m_ddragPos;  //鼠标点击点记录
    softkeyboard *loginkeyboard;    //软键盘
    VerifyImgFrame *m_VerifyImgFrame;  //验证码

    void init();   //初始化函数
    HHnet *hHnet;
    QString verifyCode;

    QMovie *movie;
    QLabel *loading;
};

#endif // LOGIN_H
