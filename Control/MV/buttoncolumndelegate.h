#pragma once

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QTableView>

class ButtonColumnDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	ButtonColumnDelegate(QObject *parent);
	~ButtonColumnDelegate();

	QWidget * createEditor(QWidget *parent,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor,
		const QModelIndex &index) const;

	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;

	public slots:
	void cellEntered(const QModelIndex &index);

private:
	QTableView *myWidget;
	QPushButton *btn;
	bool isOneCellInEditMode;
	QPersistentModelIndex currentEditedCellIndex;
};
