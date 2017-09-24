/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#ifndef ADDACCOUNT_H
#define ADDACCOUNT_H

#include <QWidget>

namespace Ui {
class AddAccount;
}

class AddAccount : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddAccount(QWidget *parent = 0);
    ~AddAccount();
    
private:
    Ui::AddAccount *ui;
};

#endif // ADDACCOUNT_H
