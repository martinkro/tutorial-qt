#include "XBasePage.h"
#include <QStyleOption>
#include <QStylePainter>

XBasePage::XBasePage(QWidget* parent) :
    QWidget(parent)
{

}

void XBasePage::paintEvent(QPaintEvent* e)
{
    QStylePainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}