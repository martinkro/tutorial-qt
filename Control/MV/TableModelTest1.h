#ifndef TABLE_MODEL_TEST1_H
#define TABLE_MODEL_TEST1_H

#include "DataRow.h"

#include <memory>
#include <QAbstractTableModel>
#include <vector>

class QSpinBox;

class TableModelTest1 : public QAbstractTableModel
{
public:
	// Will take ownership of this vector
	TableModelTest1(std::vector<std::unique_ptr<DataRow>> & rowsInfo, QObject * parent = 0);


	// Basic required information
	int columnCount(const QModelIndex & parent = QModelIndex()) const override;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	QVariant data(const QModelIndex & index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;


	// Make it editable
	Qt::ItemFlags flags(const QModelIndex & index) const override;
	bool setData(const QModelIndex & index, const QVariant & value,
		int role = Qt::EditRole) override;

	void SetEditorData(QWidget *editor, const QModelIndex &index) const;
	void SetDataFromEditor(QWidget * editor, const QModelIndex & index);

private:
	bool IndexIsValid(const QModelIndex & index) const;

	// Will be stored with rowsInfo[row] being responsible for the displayed at the given row.
	std::vector<std::unique_ptr<DataRow>> rowsInfo;
};

#include <QStyledItemDelegate>

// Note: This class will only work when the used model is MyModel
class TableItemTest1Delegate : public QStyledItemDelegate
{
public:
	explicit TableItemTest1Delegate(QObject *parent = 0);

	void setEditorData(QWidget *editor, const QModelIndex &index) const override;

	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;
};

#endif // TABLE_MODEL_TEST1_H