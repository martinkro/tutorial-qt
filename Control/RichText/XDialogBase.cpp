#include "XDialogBase.h"
#include <QStyleOption>
#include <QStylePainter>

XDialogBase::XDialogBase(QWidget* parent) :
    QDialog(parent)
{

}

void XDialogBase::paintEvent(QPaintEvent* e)
{
    QDialog::paintEvent(e);
}