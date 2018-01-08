#include "PopupMenu.h"
#include <QEvent>
#include <windows.h>

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

bool PopupMenu::event(QEvent* e)
{
    static bool class_amended = false;
    if (e->type() == QEvent::WinIdChange)
    {
        HWND hwnd = reinterpret_cast<HWND>(winId());
        if (class_amended == false)
        {
            class_amended = true;
            DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
            class_style &= ~CS_DROPSHADOW;
            ::SetClassLong(hwnd, GCL_STYLE, class_style);
        }

    }
    return QMenu::event(e);
}