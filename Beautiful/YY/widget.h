/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "other/gloweffect.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void loginMainWidgetFinished(QString name);
    
private:
    Ui::Widget *ui;

    void init();
};

#endif // WIDGET_H
