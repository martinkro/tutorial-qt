/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

Widget::~Widget()
{

    delete ui;
}


void Widget::init()
{
    setWindowFlags(Qt::FramelessWindowHint);  //ÒþÈ¥´°¿Ú±ß¿ò
    setAttribute(Qt::WA_TranslucentBackground, true);  //ÉèÖÃ´°¿Ú±³¾°Í¸Ã÷

    GlowEffect *effect = new GlowEffect(this);
    effect->setRadius(10);
    effect->setGlowColor(Qt::white);
    ui->title->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(1, 1);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(100);
    ui->main_bkg_frame->setGraphicsEffect(shadow_effect);

    return;
}

void Widget::loginMainWidgetFinished(QString name)
{
    ui->nickname->setText(name);
 //   qDebug() << "name=" << name;
}
