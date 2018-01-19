#include "TestTableModel.h"


#include <QDebug>

static const int PER_ROW_COUNT = 2;

void populateData(QList<EncryptFileItem>& dataSet)
{
    for (int i = 0; i < 27; i++)
    {
        EncryptFileItem item;
        item.filename = "Assembly-CSharp.dll";
        item.checked = Qt::Checked;
        item.realChecked = Qt::Checked;
        dataSet.append(item);
    }
}

EncryptFileTableModel::EncryptFileTableModel(QObject* parent)
	:QAbstractTableModel(parent),
	dataSet(),
	isDirty(false)
{
    populateData(dataSet);
}
int EncryptFileTableModel::rowCount(const QModelIndex& parent) const {
	//PackConfiguration* configuration = qobject_cast<PackConfiguration*>(this->parent());
	//if (configuration)
	//{
	//	qDebug() << "parent is pack configuartion";
	//}
	
	if (dataSet.size() % PER_ROW_COUNT == 0)
	{
		return dataSet.size() / PER_ROW_COUNT;
	}
	else {
		return (dataSet.size() / PER_ROW_COUNT) + 1;
	}
}
int EncryptFileTableModel::columnCount(const QModelIndex& parent) const
{
	return PER_ROW_COUNT;
}
QVariant EncryptFileTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

    int row = index.row();
    int col = index.column();
    int idx = row * PER_ROW_COUNT + col;
    if (idx >= dataSet.size())
    {
        return QVariant();
    }

	if (role == Qt::TextAlignmentRole)
	{
		return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
	}

    const EncryptFileItem& item = dataSet.value(idx);
	if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
    {
        return item.filename;
	}

	if (role = Qt::CheckStateRole)
	{
		return item.checked;
	}

	return QVariant();
}
Qt::ItemFlags EncryptFileTableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
    {
		return QAbstractItemModel::flags(index);
	}

    int row = index.row();
    int col = index.column();
    int idx = row * PER_ROW_COUNT + col;
    if (idx >= dataSet.size()) return 0;

	Qt::ItemFlags flags = QAbstractItemModel::flags(index); 
	flags |= Qt::ItemIsUserCheckable;
	flags &= ~Qt::ItemIsSelectable;
	return flags;

	//return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
}

bool EncryptFileTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::CheckStateRole)
	{
		int idx = index.row() * PER_ROW_COUNT + index.column();
		Qt::CheckState state = qvariant_cast<Qt::CheckState>(value);
		dataSet[idx].checked = state;
		isDirty = true;
		emit dataChanged(index, index);
		return true;
	}
	return QAbstractTableModel::setData(index, value, role);
}

void EncryptFileTableModel::saveData()
{
	if (!isDirty) return;
	QStringList list;
	for (auto it = dataSet.begin(); it != dataSet.end(); it++)
	{
		it->realChecked = it->checked;
		if (it->realChecked == Qt::Checked)
		{
			list.append(it->filename);
		}
	}

	//PackConfiguration::getInstance()->soDllList = list;
	isDirty = false;
}

void EncryptFileTableModel::restoreData()
{
	if (!isDirty) return;
	for (auto it = dataSet.begin(); it != dataSet.end(); it++)
	{
		it->checked = it->realChecked;
	}
	isDirty = false;
}

