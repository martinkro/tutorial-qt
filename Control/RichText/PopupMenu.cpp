#include "PopupMenu.h"

PopupMenu::PopupMenu(int x, int y, QWidget* parent) :
    QMenu(parent),
    dx(x),
    dy(y)
{

}

void PopupMenu::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    this->move(p.x() + dx, p.y() + dy);
    QMenu::showEvent(event);
}