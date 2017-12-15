#include "SimpleTreeModel2.h"

SimpleTreeModel2::SimpleTreeModel2(const QString& data, QObject* parent) :
	QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Title" << "Summary";
	root = new SimpleTreeNode2(rootData);
	setupModel(data.split(QString("\n")), root);
}

void SimpleTreeModel2::setupModel(const QStringList& lines, SimpleTreeNode2* p)
{
	// ·ÇµÝ¹é½âÎö
	QList<SimpleTreeNode2*> parents;
	QList<int> indentations;
	parents << p;
	indentations << 0;

	int number = 0;

	while (number < lines.count()) {
		int position = 0;
		while (position < lines[number].length()) {
			if (lines[number].at(position) != ' ')
				break;
			position++;
		}

		QString lineData = lines[number].mid(position).trimmed();

		if (!lineData.isEmpty()) {
			// Read the column data from the rest of the line.
			QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
			QList<QVariant> columnData;
			for (int column = 0; column < columnStrings.count(); ++column)
				columnData << columnStrings[column];

			if (position > indentations.last()) {
				// The last child of the current parent is now the new parent
				// unless the current parent has no children.

				if (parents.last()->childCount() > 0) {
					parents << parents.last()->child(parents.last()->childCount() - 1);
					indentations << position;
				}
			}
			else {
				while (position < indentations.last() && parents.count() > 0) {
					parents.pop_back();
					indentations.pop_back();
				}
			}

			// Append a new item to the current parent's list of children.
			parents.last()->appendChild(new SimpleTreeNode2(columnData, parents.last()));
		}

		++number;
	}
}

Qt::ItemFlags SimpleTreeModel2::flags(const QModelIndex& index)const {
	if (!index.isValid()) return 0;
	if (index.column() == 0) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsSelectable;
	return QAbstractItemModel::flags(index);
}

int SimpleTreeModel2::rowCount(const QModelIndex& parent)const
{
	SimpleTreeNode2* node;
	if (parent.column() > 0) return 0;
	if (!parent.isValid())
	{
		node = root;
	}
	else
	{
		node = static_cast<SimpleTreeNode2*>(parent.internalPointer());
	}
	return node->childCount();
}

int SimpleTreeModel2::columnCount(const QModelIndex& index)const {
	if (index.isValid())
	{
		return static_cast<SimpleTreeNode2*>(index.internalPointer())->columnCount();
	}
	else
	{
		return root->columnCount();
	}
}

QVariant SimpleTreeModel2::data(const QModelIndex& index, int role)const {
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		if (checkedList.contains(index)) return Qt::Checked;
		else return Qt::Unchecked;
	}

	if (role == Qt::DisplayRole)
	{
		SimpleTreeNode2* node = static_cast<SimpleTreeNode2*>(index.internalPointer());
		return node->data(index.column());
	}
	return QVariant();
}

QVariant SimpleTreeModel2::headerData(int section, Qt::Orientation orientation, int role)const {
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return root->data(section);
	}
	return QVariant();
}

QModelIndex SimpleTreeModel2::index(int row, int column, const QModelIndex& parent)const {
	if (!hasIndex(row, column, parent)) return QModelIndex();

	SimpleTreeNode2* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<SimpleTreeNode2*>(parent.internalPointer());

	SimpleTreeNode2* child = p->child(row);
	if (child) return createIndex(row, column, child);
	else return QModelIndex();
}

QModelIndex SimpleTreeModel2::parent(const QModelIndex& index)const {
	if (!index.isValid()) return QModelIndex();

	SimpleTreeNode2* child = static_cast<SimpleTreeNode2*>(index.internalPointer());
	SimpleTreeNode2* parent = child->parent;
	if (parent == root) return QModelIndex();

	return createIndex(parent->row(), 0, parent);
}

bool SimpleTreeModel2::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		if (value == Qt::Unchecked)
		{
			checkedList.removeOne(index);
			emit dataChanged(index, index);
		}
		else if (value == Qt::Checked)
		{
			checkedList.append(index);
			emit dataChanged(index, index);
		}

		int childCount = rowCount(index);
		if (childCount > 0)
		{
			for (int i = 0; i < childCount; i++)
			{
				QModelIndex child = this->index(i, 0, index);
				setData(child, value, Qt::CheckStateRole);
			}
		}
	}
	return true;
}