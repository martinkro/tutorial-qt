#ifndef POPUP_MENU_H
#define POPUP_MENU_H

#include <QMenu>
class QShowEvent;

class PopupMenu:public QMenu
{
    Q_OBJECT
public:
    explicit PopupMenu(int x = 0,int y = 0,QWidget *parent = Q_NULLPTR);
    void showEvent(QShowEvent* event);

private:
    int dx;
    int dy;
};

#endif