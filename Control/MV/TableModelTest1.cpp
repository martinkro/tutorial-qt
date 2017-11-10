#include "TableModelTest1.h"

TableModelTest1::TableModelTest1(std::vector<std::unique_ptr<DataRow>> & rowsInfo, QObject * parent /* = 0*/)
	: QAbstractTableModel(parent)
{
	std::swap(this->rowsInfo, rowsInfo);
}

int TableModelTest1::columnCount(const QModelIndex & /*parent = QModelIndex()*/) const
{
	if (rowsInfo.size() == 0)
		return 0;

	// If you will have rows with different columns, then this will need to instead be the max value
	return rowsInfo[0]->GetColumnCount();
}


int TableModelTest1::rowCount(const QModelIndex & /* parent = QModelIndex()*/) const
{
	return rowsInfo.size();
}


QVariant TableModelTest1::data(const QModelIndex & index, int role) const
{
	if (!IndexIsValid(index))
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return rowsInfo[index.row()]->GetData(index.column());

	return QVariant();
}


QVariant TableModelTest1::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	// If you are displaying headers, will want to add more code here
	if (orientation == Qt::Horizontal)
		return QString("Column %1").arg(section);
	else
		return QString("Row %1").arg(section);
}


Qt::ItemFlags TableModelTest1::flags(const QModelIndex & index) const
{
	if (!IndexIsValid(index))
		return Qt::ItemIsEnabled;

	if (rowsInfo[index.row()]->CanBeChanged(index.column()))
		return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;

	return QAbstractTableModel::flags(index);

	/* Optional setting. Makes it so cannot select indexes that can't be changed (need to remove above return as well)
	// If you don't know what this does, look at http://stackoverflow.com/questions/3920307/how-can-i-remove-a-flag-in-c
	return QAbstractTableModel::flags(index) & ~Qt::ItemIsSelectable;
	*/
}

bool TableModelTest1::setData(const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole*/)
{
	if (IndexIsValid(index) && role == Qt::EditRole) {
		rowsInfo[index.row()]->DataChanged(index.column(), value);
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

bool TableModelTest1::IndexIsValid(const QModelIndex & index) const
{
	return index.isValid() && index.row() < rowCount();
}

void TableModelTest1::SetEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (IndexIsValid(index))
		rowsInfo[index.row()]->SetEditorData(editor, index.column());
}

void TableModelTest1::SetDataFromEditor(QWidget * editor, const QModelIndex & index)
{
	if (IndexIsValid(index))
		rowsInfo[index.row()]->SetDataFromEditor(editor, index.column());
}

// TableItemTest1Delegate

TableItemTest1Delegate::TableItemTest1Delegate(QObject *parent /*= 0*/)
	: QStyledItemDelegate(parent)
{

}

void TableItemTest1Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	const TableModelTest1* model = static_cast<const TableModelTest1*>(index.model());

	model->SetEditorData(editor, index);
}

void TableItemTest1Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	TableModelTest1* myModel = static_cast<TableModelTest1*>(model);

	myModel->SetDataFromEditor(editor, index);
}