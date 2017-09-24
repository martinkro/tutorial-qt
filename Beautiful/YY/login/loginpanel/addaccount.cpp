/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#include "addaccount.h"
#include "ui_addaccount.h"

AddAccount::AddAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAccount)
{
    ui->setupUi(this);
}

AddAccount::~AddAccount()
{
    delete ui;
}
