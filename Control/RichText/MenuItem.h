#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <QWidget>
#include <QFrame>

class MenuItem:public QFrame
{
    Q_OBJECT
public:
    MenuItem(const QString& text, QWidget* parent = 0);

protected:
    void paintEvent(QPaintEvent* event)override;

};


#endif