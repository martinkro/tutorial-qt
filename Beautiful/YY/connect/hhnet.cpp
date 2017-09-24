/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#include "hhnet.h"

HHnet::HHnet(QObject *parent) :
    QObject(parent)
{
    pCookieJar=new QNetworkCookieJar(this);
    http=new QNetworkAccessManager(this);

    http->setCookieJar(pCookieJar);

    connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpFinished(QNetworkReply*)));

 //   QTime time;
 //   time= QTime::currentTime();
  //  qsrand(time.msec()+time.second()*1000);
  //  clientid=QString::number(qrand());
    clientid = QString("10116933");
}


void HHnet::httpFinished(QNetworkReply* reply){
    QByteArray replyData=reply->readAll();
    reply->deleteLater();
    QString replystr=QString::fromUtf8(replyData);
 //   bool isok;
    switch(httpAction){
    case NoAction:
        break;
    case CheckVerirycodeAction:
        replystr.chop(3);  //字符串后面移除3个字符
        uinhexstr=replystr.section("','",2,2).left(32);
        if(replystr.indexOf("'0'")>-1){
            emit checkVerifycodeFinished(true,replystr.mid(18,4));
        }else{
            emit checkVerifycodeFinished(false,replystr.mid(18,4));
        }
        qDebug()<<replystr<<uinhexstr<<endl;
        break;
    case GetVerifyImgAction:
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        emit getVerifyImgFinished(replyData);
        httpAction = NoAction;
        break;
    case LoginAction:
        qDebug()<<"------------"<<replystr<<endl;
        if(replystr.indexOf("ptuiCB('0'")>-1){
            ptwebhh = getCookie("ptwebqq");
            QString tempstr = replystr;
            tempstr.chop(5);
            nickname = tempstr.section(",", -1, -1).remove(0, 2);
            qDebug()<<"get cookie ptwebqq="<<ptwebhh<<endl;
        }
        if(!ptwebhh.isEmpty()){
            check_sig(replystr);
        }
        if(replystr.indexOf("ptuiCB('3'")>-1){
            emit loginErrorInf(3, QString("您输入的密码有误，请重试。"));
        }
        if(replystr.indexOf("ptuiCB('4'")>-1){
            emit loginErrorInf(4, QString("您输入的验证码不正确，请重新输入。"));
        }
        break;
    case Check_sigAction:
        login2();
        qDebug() << reply->readAll();
        break;
    case Login2Action:
        qDebug()<<"Login2Action"<<replystr<<endl;
        if(!(replystr.section(",", 0, 0).right(1) == QString("0"))){
            emit loginFinished(false,"登录失败！");
        }else{
            uin=replystr.section(",", 1, 1).right(10);
            qDebug()<<"uin="<<uin<<endl;
            vfwebqq=replystr.section(",", 6, 6).right(80);
            psessionid=replystr.section(",", 7, 7).remove(0, 14);
            //qDebug()<<"登录成功！vfwebqq="<<vfwebqq<<"psessionid="<<psessionid<<endl;
            emit loginFinished(true,"成功！");
       //     this->getUserFriends();

        }
        //qDebug()<<replystr<<endl;
        //qDebug()<<replystr<<endl<<http->cookieJar()->cookiesForUrl(QUrl("http://www.qq.com/"));*/
        break;
    }
}

void HHnet::checkVerifyCode(QString hhnum){
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://check.ptlogin2.qq.com/check?uin=%1&appid=1003903&r=0.6331230279734333").arg(hhnum)));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","check.ptlogin2.qq.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.62 Safari/537.36");

    httpAction = CheckVerirycodeAction;
    http->get(request);
}

void HHnet::getVerifyImg(QString hhnum){
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://captcha.qq.com/getimage?aid=1003903&uin=%1").arg(hhnum)));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","captcha.qq.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.62 Safari/537.36");
    httpAction = GetVerifyImgAction;
    http->get(request);
}

void HHnet::login(QString hhnum,QString hhpass, QString verifyCode){
    qDebug()<< "p=" <<getP(hhpass,verifyCode,uinhexstr);
    QNetworkRequest request;
    QString urlstr=QString("http://ptlogin2.qq.com/login?u=%1&p=%2&verifycode=%3&webqq_type=10&remember_uin=1&login2qq=1&aid=1003903&u1=%4&h=1&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=2-11-12939&mibao_css=m_webqq&t=1&g=1&js_type=0&js_ver=10041&login_sig=Ip4V0YQezz6DEwpsE*-Cq*4NWVecBqWZYbNS22JCEQIT-sp20PyQtj8f-pqSIREa").arg(hhnum).arg(getP(hhpass,verifyCode,uinhexstr)).arg(verifyCode).arg("http%3A%2F%2Fweb2.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10");
	QUrl tempUrl(urlstr);
    //tempUrl.setEncodedUrl(urlstr.toAscii());
    request.setUrl(tempUrl);
     qDebug()<<urlstr<<endl;
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","ptlogin2.qq.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.62 Safari/537.36");
    httpAction = LoginAction;
    http->get(request);
}

void HHnet::check_sig(QString urlstr){
    urlstr=urlstr.mid(16);
    urlstr=urlstr.left(urlstr.indexOf('\''));
    //qDebug()<<urlstr<<endl;return;
    QNetworkRequest request;
    QUrl tempUrl(urlstr);
    // tempUrl.setEncodedUrl(urlstr.toAscii());
    request.setUrl(tempUrl);
     qDebug()<<urlstr<<endl;
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","ptlogin2.qq.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.62 Safari/537.36");
    httpAction = Check_sigAction;
    http->get(request);
}

void HHnet::login2(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://d.web2.qq.com/channel/login2"));
    request.setRawHeader("Accept","*/*");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8,en-US;q=0.6,en;q=0.4");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    request.setRawHeader("Host","d.web2.qq.com");
    request.setRawHeader("Origin","http://d.web2.qq.com");
    request.setRawHeader("Referer","http://d.web2.qq.com/proxy.html?v=20110331002&callback=2");
    request.setRawHeader("User-Agent","Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.62 Safari/537.36");
    QByteArray postData;
    postData.append("r="+QUrl::toPercentEncoding(QString("{\"status\":\"online\",\"ptwebqq\":\"%1\",\"passwd_sig\":\"\",\"clientid\":\"%2\",\"psessionid\":null}").arg(ptwebhh).arg(clientid)));
    postData.append(QString("&clientid=%1&psessionid=null").arg(clientid));
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.size());
    httpAction = Login2Action;
    qDebug()<<postData<<endl;
    http->post(request,postData);

}


QString HHnet::getCookie(const QString &name){
    QString retstr;
    foreach(QNetworkCookie cookie , http->cookieJar()->cookiesForUrl(QUrl("http://www.qq.com/"))){
        // qDebug()<<cookie<<endl;
        if(cookie.name()==name){
            retstr=cookie.value();
        }
    }
    return retstr;
}

QString HHnet::getP(QString hhpass, QString verifyCode, QString uinhexstr){
    qDebug() <<"getP"<< hhpass <<verifyCode<<uinhexstr;
#ifdef _USE_JS_
    QScriptEngine engine;       //创建一个QScriptEngine对象
    QFile scriptFile("encodepwd.js");
    scriptFile.open(QIODevice::ReadOnly);    //设为只读
    QString script(scriptFile.readAll());    //讲js中的所有内容读取到QString中
    scriptFile.close();
    QScriptValue temp1(&engine, uinhexstr);      //关联参数
    engine.globalObject().setProperty("x", temp1);     //使得参数在js中可以以x的方式被调用
    QScriptValue temp2(&engine, hhpass);     //关联参数
    engine.globalObject().setProperty("y", temp2);  //使得参数在js中可以以y的方式被调用
    QScriptValue temp3(&engine, verifyCode);       //关联参数
    engine.globalObject().setProperty("z", temp3);  //使得参数在js中可以以z的方式被调用

    QScriptValue result = engine.evaluate(script);   //得到js处理后的返回值
    qDebug()<<"getP<" << result.toString();
    return result.toString();
#else
    QByteArray qqpassbyte=QCryptographicHash::hash(hhpass.toLatin1(),QCryptographicHash::Md5);
    QByteArray uinhexbyte = QByteArray::fromHex(uinhexstr.toLatin1());
    qDebug()<<"uinhexbyte="<<uinhexbyte<<"uinstr="<<uinhexstr<<endl;
    QByteArray qqpassuinbyte=QCryptographicHash::hash(qqpassbyte+uinhexbyte,QCryptographicHash::Md5).toHex().toUpper();
    QByteArray byteP=QCryptographicHash::hash(qqpassuinbyte+verifyCode.toUpper().toLatin1(),QCryptographicHash::Md5).toHex().toUpper();
    qDebug()<<QString::fromLatin1(byteP);
    return QString::fromLatin1(byteP);

#endif
}


void HHnet::printInf(QString str)
{
    QFile f("./debugInf.txt");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }

    QTextStream txtOutput(&f);
    txtOutput << str << endl;
    f.close();
}
