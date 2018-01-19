#include "XCheckBoxDelegate.h"
#include <QApplication>
#include <QVariant>
#include <QPainter>

const int TABLE_HEIGHT = 30;
XCheckBoxDelegate::XCheckBoxDelegate(QWidget* parent)
    :QStyledItemDelegate(parent)
{

}

QRect XCheckBoxDelegate::CheckBoxRect(const QStyleOptionViewItem &option)
{
    QStyleOptionButton checkboxOption;
    QRect checkboxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxOption);
    QPoint checkboxPoint(option.rect.x() + option.rect.width() / 2 - checkboxRect.width() / 2,
        option.rect.y() + option.rect.height() / 2 - checkboxRect.height() / 2);
    return QRect(checkboxPoint, checkboxRect.size());
}
void XCheckBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
    if (index.isValid() && index.column() == 0)
    {
        //paintDefault(painter, option, index);
        //return;
    }
    return QStyledItemDelegate::paint(painter, option, index);
}
QSize XCheckBoxDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(TABLE_HEIGHT);
    return size;
}

void XCheckBoxDelegate::paintDefault(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
    Qt::CheckState state = qvariant_cast<Qt::CheckState>(index.data(Qt::CheckStateRole));
    QString filename = index.data(Qt::DisplayRole).toString();
    QStyleOptionButton checkboxOption;
    checkboxOption.text = filename;
    checkboxOption.state |= QStyle::State_Enabled;
    if (state == Qt::Checked) {
        checkboxOption.state |= QStyle::State_On;
    }
    else {
        checkboxOption.state |= QStyle::State_Off;
    }
    
    QStyleOptionButton opt;
    //initStyleOption(&opt,index);
    QSize m_decoratorSize(15, 15);
    int m_decoratorMargin = 10;
    QStyleOptionButton subopt = opt;
    subopt.rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &opt);
    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &subopt, painter);
    subopt.rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxContents, &opt);
    painter->fillRect(QRect(subopt.rect.topLeft() + QPoint(m_decoratorMargin, 0), m_decoratorSize), QBrush(Qt::green));

    subopt.rect.translate(m_decoratorSize.width() + m_decoratorMargin * 2, 0);
    QApplication::style()->drawControl(QStyle::CE_CheckBoxLabel, &subopt, painter);
    if (opt.state & QStyle::State_HasFocus) {
        QStyleOptionFocusRect fropt;
        fropt.rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxFocusRect, &opt);
        fropt.rect.setRight(fropt.rect.right() + m_decoratorSize.width() + m_decoratorMargin * 2);
        QApplication::style()->drawPrimitive(QStyle::PE_FrameFocusRect, &fropt, painter);
    }
}

//void XCheckBoxDelegate::paintDefault1(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
//{
//    Qt::CheckState state = qvariant_cast<Qt::CheckState>(index.data(Qt::CheckStateRole));
//    QString filename = index.data(Qt::DisplayRole).toString();
//    QStyleOptionButton checkboxOption;
//    checkboxOption.text = filename;
//    checkboxOption.state |= QStyle::State_Enabled;
//    if (state == Qt::Checked) {
//        checkboxOption.state |= QStyle::State_On;
//    }
//    else {
//        checkboxOption.state |= QStyle::State_Off;
//    }
//    //checkboxOption.rect = XCheckBoxDelegate::CheckBoxRect(option);
//    checkboxOption.rect = option.rect;
//    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, painter);
//
//    //QStyledItemDelegate::paint(painter, option, index);
//    QStyleOptionViewItem itemOption(option);
//    if (itemOption.state & QStyle::State_HasFocus)
//        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
//    // QStyledItemDelegate::paint(painter, itemOption, index);
//    //QPen oldPen = painter->pen();
//    //painter->setPen(pen);
//    painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
//    //painter->drawLine(itemOption.rect.bottomLeft(), itemOption.rect.bottomRight());
//    //painter->setPen(oldPen);
//}