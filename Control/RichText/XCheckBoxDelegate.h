#ifndef XCHECKBOX_DELEGATE_H
#define XCHECKBOX_DELEGATE_H

#include <QStyledItemDelegate>

class XCheckBoxDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit XCheckBoxDelegate(QWidget* parent);
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    static QRect CheckBoxRect(const QStyleOptionViewItem &option);

    void paintDefault(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const;
    //void paintDefault1(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const;
};


#endif