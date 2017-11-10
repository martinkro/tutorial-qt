#pragma once

#include <QStyledItemDelegate>

class SpinBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	SpinBoxDelegate(QObject *parent);
	~SpinBoxDelegate();

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const Q_DECL_OVERRIDE;

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
};
