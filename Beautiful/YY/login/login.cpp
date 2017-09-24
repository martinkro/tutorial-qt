/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#include "login.h"
#include "ui_login.h"
#include <QDebug>



Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    init();  //��ʼ������   
}

Login::~Login()
{
    if (!loginkeyboard->isHidden())    //�ȰѼ������أ���ֹ�����ڹرձ���������ز��ͷŵ�
        loginkeyboard->hide();
    loginkeyboard->deleteLater();   //�������ǲ�û��ָ������̵ĸ��࣬�����������ֶ�del
    delete ui;
}


void Login::init()
{
    setWindowFlags(Qt::FramelessWindowHint);  //��ȥ���ڱ߿�
    setAttribute(Qt::WA_TranslucentBackground, true);  //���ô��ڱ���͸��

    ui->id->lineEdit()->setPlaceholderText(QString("HH����/�ֻ�/����"));
    ui->keyboard->installEventFilter(this);  //ע����Ӷ���keyboard���¼�������

    loginkeyboard = new softkeyboard();//newһ�������
    connect(loginkeyboard, SIGNAL(input(QString)), this, SLOT(softkeyboardinput(QString)));  //������������뵽���������
    loginkeyboard->hide();   //�����������

    hHnet=new HHnet(this);
    m_VerifyImgFrame = new VerifyImgFrame(ui->widget);
    connect(hHnet,SIGNAL(checkVerifycodeFinished(bool,QString)),this,SLOT(checkVerifycodeFinished(bool,QString)));
    connect(hHnet,SIGNAL(getVerifyImgFinished(QByteArray)),m_VerifyImgFrame,SLOT(getVerifyImgFinished(QByteArray)));
    connect(m_VerifyImgFrame, SIGNAL(verifyEditFinished(bool,QString)), this, SLOT(verifyCodeEditFinished(bool,QString)));
    connect(m_VerifyImgFrame, SIGNAL(clickOk()),this, SLOT(clickOk()));
    connect(hHnet,SIGNAL(loginFinished(bool,QString)),this,SLOT(loginFinished(bool,QString)));
    connect(hHnet,SIGNAL(loginErrorInf(int,QString)), this, SLOT(loginErrorInf(int,QString)));
    return;
}

void Login::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange)   //����״̬�ı�ʱ���´���
    {
        repaint();          //ˢ��ҳ�棬���򴰿ڻ�ԭ����С����ťΪpress״̬
    }

}

void Login::mousePressEvent(QMouseEvent *event)   //��굥���¼�
{
    if (event->button() == Qt::LeftButton)    //�жϰ��µ��Ƿ�Ϊ���
    {
        m_ddragPos = event->globalPos() - frameGeometry().topLeft();    //��¼���µ�λ��
        event->accept();    //�¼�����
    }
    if (!loginkeyboard->isHidden()) {     //�ж�������Ƿ�����
        loginkeyboard->hide();    //���������
        ui->keyboard->setChecked(false);   //��������̰�ťchecked״̬Ϊfalse
    }
}

void Login::mouseMoveEvent(QMouseEvent *event)      //����ƶ��¼�
{
    if (event->buttons() & Qt::LeftButton)     //�жϰ��µ��Ƿ�Ϊ���
    {
        move(event->globalPos() - m_ddragPos);     //�ƶ�����ǰλ��
        event->accept();   //�¼�����
    }
}

bool Login::eventFilter(QObject *obj, QEvent *event)   //��������̰�ť������hoverʱʹ��pwd��lineEditҲ����hoverЧ��
{
    if (obj == ui->keyboard) {
        if (event->type() == QEvent::HoverEnter) {
            ui->pwd->setStyleSheet(QString("border:2px solid gray;\
            border-top-color: qlineargradient(spread:pad, x1:0.534, y1:1, x2:0.545, y2:0, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
            border-right-color: qlineargradient(spread:pad, x1:0, y1:0.506, x2:1, y2:0.511364, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
            border-bottom-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.5, y2:1, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
            border-left-color: qlineargradient(spread:pad, x1:1, y1:0.579545, x2:0, y2:0.574, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
            padding-left:3px;\
            padding-right:25px;\
            "));
        }
        if (event->type() == QEvent::HoverLeave) {
            ui->pwd->setStyleSheet(QString("QLineEdit#pwd::hover{border:2px solid gray;\
                                           border-top-color: qlineargradient(spread:pad, x1:0.534, y1:1, x2:0.545, y2:0, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           border-right-color: qlineargradient(spread:pad, x1:0, y1:0.506, x2:1, y2:0.511364, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           border-bottom-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.5, y2:1, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           border-left-color: qlineargradient(spread:pad, x1:1, y1:0.579545, x2:0, y2:0.574, stop:0 rgba(36, 132, 238, 255), stop:0.982955 rgba(143, 192, 255, 0));}\
                                           QLineEdit#pwd{border-radius: 1px;border:2px solid gray;\
                                           border-top-color: qlineargradient(spread:pad, x1:0.471273, y1:0.71, x2:0.483, y2:0, stop:0 rgba(191, 191, 191, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           border-right-color: qlineargradient(spread:pad, x1:0.301, y1:0.510682, x2:1, y2:0.522, stop:0 rgba(191, 191, 191, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           border-bottom-color: qlineargradient(spread:pad, x1:0.523, y1:0.294455, x2:0.528, y2:1, stop:0 rgba(191, 191, 191, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           border-left-color: qlineargradient(spread:pad, x1:0.682091, y1:0.544, x2:0, y2:0.557, stop:0 rgba(191, 191, 191, 255), stop:0.982955 rgba(143, 192, 255, 0));\
                                           padding-left:3px;padding-right: 25px;font: 9pt 'Meiryo';}  "));
            return true;
        }
    }
    return QDialog::eventFilter(obj, event);
}

void Login::on_keyboard_clicked(bool checked)
{
    if (checked) {    //�Ƿ񱻰���
        loginkeyboard->move(frameGeometry().topLeft().x() + ui->keyboard->x() - loginkeyboard->width()/2 - 7, frameGeometry().topLeft().y() + 209);   //�ƶ���ָ��λ��
        loginkeyboard->show();   //��ʾ�����
    }
    else {
        loginkeyboard->hide();   //���������
    }
    return;
}


void Login::softkeyboardinput(QString str)
{
    if (str == QString("del")) {
        ui->pwd->setText(ui->pwd->text().left(ui->pwd->text().length() - 1));  //ȥ�����һ���ַ�
        return;
    }
    ui->pwd->setText(ui->pwd->text()+str);  //ͳһ������������
    return;
}

void Login::on_button_login_clicked()
{
#ifdef    _HH_DEBUG_
    accept();
    return;
#endif

    ui->id->hide();
    ui->pwd->hide();
    ui->auto_login->hide();
    ui->rem_pwd->hide();
    ui->mima->hide();
    ui->zhuce->hide();
    ui->switch_single->hide();
    ui->corner_right->hide();
    ui->keyboard->hide();

    movie = new QMovie("./images/gif/loading.gif");
    loading = new QLabel(ui->frame_4);
    loading->show();
    loading->setFixedSize(378, 2);
    loading->move(0, ui->frame_4->height()-2);
    loading->setMovie(movie);
    movie->start();

    QPropertyAnimation *animation = new QPropertyAnimation(ui->login_head, "pos");
    animation->setDuration(200);
    animation->setStartValue(QPoint(ui->login_head->x(), ui->login_head->y()));
    animation->setEndValue(QPoint(148, ui->login_head->y()));
    animation->start();

    hHnet->checkVerifyCode(ui->id->currentText().trimmed());
}

void Login::on_switch_single_clicked(bool checked)
{

}


void Login::checkVerifycodeFinished(bool getCode, QString code){
    qDebug()<<getCode<<code<<endl;
    if(getCode){
        verifyCode = code;
        hHnet->login(ui->id->currentText().trimmed(),ui->pwd->text().trimmed(), verifyCode);
    }
    else{
        ui->frame_4->hide();
        ui->frame_3->hide();
        m_VerifyImgFrame->move(0, ui->widget->height()-m_VerifyImgFrame->height());
        m_VerifyImgFrame->m_SetCurrentIndex(0);
        m_VerifyImgFrame->show();
        hHnet->getVerifyImg(ui->id->currentText().trimmed());
    }
}


void Login::verifyCodeEditFinished(bool getVerify, QString verify){
    m_VerifyImgFrame->hide();
    ui->frame_3->show();
    ui->frame_4->show();
    if (getVerify) {
        verifyCode = verify;
    }
    hHnet->login(ui->id->currentText().trimmed(),ui->pwd->text().trimmed(), verifyCode);
}


void Login::loginFinished(bool loginok, QString message){
    qDebug()<<loginok<<message<<endl;
    if(loginok){
        emit loginMainWidget(hHnet->nickname);
        accept();
    }else{
        ui->id->show();
        ui->pwd->show();
        ui->auto_login->show();
        ui->rem_pwd->show();
        ui->mima->show();
        ui->zhuce->show();
        ui->switch_single->show();
        ui->corner_right->show();
        ui->keyboard->show();
        ui->login_head->move(20, 43);
        movie->deleteLater();
        loading->deleteLater();
    }
}

void Login::loginErrorInf(int id, QString message)
{
    switch(id) {
    case 3:
        ui->frame_4->hide();
        ui->frame_3->hide();
        m_VerifyImgFrame->move(0, ui->widget->height()-m_VerifyImgFrame->height());
        m_VerifyImgFrame->m_SetCurrentIndex(1);
        m_VerifyImgFrame->show();
        break;

    case 4:
        ui->frame_4->hide();
        ui->frame_3->hide();
        m_VerifyImgFrame->move(0, ui->widget->height()-m_VerifyImgFrame->height());
        m_VerifyImgFrame->m_SetCurrentIndex(0);
        m_VerifyImgFrame->show();
        hHnet->getVerifyImg(ui->id->currentText().trimmed());

    }
    return;
}

void Login::clickOk()
{
    m_VerifyImgFrame->hide();
    ui->frame_3->show();
    ui->frame_4->show();
    ui->id->show();
    ui->pwd->show();
    ui->auto_login->show();
    ui->rem_pwd->show();
    ui->mima->show();
    ui->zhuce->show();
    ui->switch_single->show();
    ui->corner_right->show();
    ui->keyboard->show();
    ui->login_head->move(20, 43);
    movie->deleteLater();
    loading->deleteLater();
    ui->pwd->clear();
    ui->pwd->setFocus();
    return;
}
