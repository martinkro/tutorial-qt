#include "XTableView.h"
#include <QDebug>

XTableView::XTableView(QWidget* parent) :
    QTableView(parent)
{

}


QSize XTableView::minimumSizeHint()const
{
    QSize size = QTableView::minimumSizeHint();
    qDebug() << "XTableView::minimumSizeHint():" << size;
    return size;
}
QSize XTableView::sizeHint()const
{
    QSize size = QTableView::sizeHint();
    qDebug() << "XTableView::sizeHint():" << size;
    return size;
}


QSize XTableView::viewportSizeHint() const
{
    QSize size = QTableView::viewportSizeHint();
    qDebug() << "XTableView::viewportSizeHint():" << size;
    
    return size;
}
void XTableView::scrollContentsBy(int dx, int dy)
{
    QTableView::scrollContentsBy(dx, dy);
    qDebug() << "XTableView::scrollContentsBy():" << dx << ":" << dy;
}
void XTableView::updateGeometries()
{
    QTableView::updateGeometries();
    QSize s = this->sizeHint();
    qDebug() << "<1>XTableView::updateGeometries():" << this->size();
    qDebug() << "<2>XTableView::updateGeometries():" << s;
    //this->setMinimumHeight(s.height());
    qDebug() << "<3>XTableView::updateGeometries():" << this->size();
}

void XTableView::showEvent(QShowEvent* e)
{
    qDebug() << "<1>XTableView::showEvent():" << this->size();
    qDebug() << "<2>XTableView::showEvent():" << this->sizeHint();
    QTableView::showEvent(e);
}
void XTableView::paintEvent(QPaintEvent* e)
{
    qDebug() << "<1>XTableView::paintEvent():" << this->size();
    qDebug() << "<2>XTableView::paintEvent():" << this->sizeHint();
    QTableView::paintEvent(e);
}