/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#ifndef HHNET_H
#define HHNET_H

#define _USE_JS_

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QtScript/QtScript>

enum HttpAction{NoAction, CheckVerirycodeAction, LoginAction, Check_sigAction, Login2Action, GetVerifyImgAction};

class HHnet : public QObject
{
    Q_OBJECT
public:
    explicit HHnet(QObject *parent = 0);
    
signals:
    void checkVerifycodeFinished(bool getCode,QString code);
    void getVerifyImgFinished(const QByteArray imgdata);
    void loginFinished(bool loginok,QString message);
    void loginErrorInf(int id, QString message);
    
public slots:
    void httpFinished(QNetworkReply*);

public:
    void checkVerifyCode(QString hhnum);
    void login(QString hhnum,QString hhpass, QString verifyCode);
    void login2();
    void getVerifyImg(QString hhnum);

    HttpAction httpAction;
    QString uin;
    QString nickname;

private:
    QNetworkCookieJar *pCookieJar;
    QNetworkAccessManager *http;


    QString clientid;
    QString uinhexstr;
    QString ptwebhh;

    QString vfwebqq;
    QString psessionid;

private:
    QString getCookie(const QString &name);
    void check_sig(QString urlstr);
    QString getP(QString hhpass, QString verifyCode, QString uinhexstr);

    void printInf(QString str);
};

#endif // HHNET_H
