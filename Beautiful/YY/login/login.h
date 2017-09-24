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
    void changeEvent(QEvent *event);    //����״̬�仯
    void mousePressEvent(QMouseEvent *event);   //��갴��
    void mouseMoveEvent(QMouseEvent *event);    //����ƶ�
    bool eventFilter(QObject *obj, QEvent *event);    //�¼�����

signals:
    void loginMainWidget(QString name);
    
private slots:
    void on_keyboard_clicked(bool checked);  //����̵��
    void softkeyboardinput(QString str);    //�����������

    void on_button_login_clicked();    //��¼��ť���
    void on_switch_single_clicked(bool checked);  //���û���½��ť

    void checkVerifycodeFinished(bool getCode,QString code);
    void verifyCodeEditFinished(bool getVerify, QString verify);
    void loginFinished(bool loginok, QString message);
    void loginErrorInf(int id, QString message);
    void clickOk();

private:
    Ui::Login *ui;
    QPoint  m_ddragPos;  //��������¼
    softkeyboard *loginkeyboard;    //�����
    VerifyImgFrame *m_VerifyImgFrame;  //��֤��

    void init();   //��ʼ������
    HHnet *hHnet;
    QString verifyCode;

    QMovie *movie;
    QLabel *loading;
};

#endif // LOGIN_H
