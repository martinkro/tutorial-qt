/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#include "verifyimgframe.h"
#include "ui_verifyimgframe.h"
#include <QDebug>

VerifyImgFrame::VerifyImgFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VerifyImgFrame)
{
    ui->setupUi(this);
    this->hide();

    QGraphicsDropShadowEffect *shadow_effect_ok = new QGraphicsDropShadowEffect(this);  //添加按钮下方阴影
    shadow_effect_ok->setOffset(0, 1);
    shadow_effect_ok->setColor(Qt::gray);
    shadow_effect_ok->setBlurRadius(4);
    ui->ok->setGraphicsEffect(shadow_effect_ok);

    QGraphicsDropShadowEffect *shadow_effect_cancel = new QGraphicsDropShadowEffect(this);  //添加按钮下方阴影
    shadow_effect_cancel->setOffset(0, 1);
    shadow_effect_cancel->setColor(Qt::gray);
    shadow_effect_cancel->setBlurRadius(4);
    ui->cancel->setGraphicsEffect(shadow_effect_cancel);
}

VerifyImgFrame::~VerifyImgFrame()
{
    delete ui;
}

void VerifyImgFrame::getVerifyImgFinished(QByteArray imgdata){
    qDebug()<<"getVerifyImgFinished"<<endl;
    qDebug()<<imgdata.length()<<endl;
    QPixmap p;
    p.loadFromData(imgdata);
    ui->verifyImg->setPixmap(p);
}

void VerifyImgFrame::on_ok_clicked()
{
    emit verifyEditFinished(true, ui->lineEdit->text().trimmed().toUpper());
}

void VerifyImgFrame::on_cancel_clicked()
{
    emit verifyEditFinished(false, ui->lineEdit->text().trimmed().toUpper());
}

void VerifyImgFrame::m_SetCurrentIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    return;
}


void VerifyImgFrame::on_pushButton_clicked()
{
    emit clickOk();
}
