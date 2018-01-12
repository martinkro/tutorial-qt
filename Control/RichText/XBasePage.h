#ifndef XBASEPAGE_H
#define XBASEPAGE_H

#include <QWidget>

class XBasePage:public QWidget
{
    Q_OBJECT
public:
    explicit XBasePage(QWidget* parent = 0);

protected:
    void paintEvent(QPaintEvent* e);
    
};


#endif