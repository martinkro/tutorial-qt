#include "SimpleTreeModel3.h"

SimpleTreeModel3::SimpleTreeModel3(const QString& data, QObject* parent) :
	QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Title" << "Summary";
	root = new SimpleTreeNode3(rootData);
	setupModel(data.split(QString("\n")), root);
}

void SimpleTreeModel3::setupModel(const QStringList& lines, SimpleTreeNode3* p)
{
	// 非递归解析
	QList<SimpleTreeNode3*> parents;
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
			parents.last()->appendChild(new SimpleTreeNode3(columnData, parents.last()));
		}

		++number;
	}
}

Qt::ItemFlags SimpleTreeModel3::flags(const QModelIndex& index)const {
	if (!index.isValid()) return 0;
	if (index.column() == 0) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
	return QAbstractItemModel::flags(index);
}

int SimpleTreeModel3::rowCount(const QModelIndex& parent)const
{
	SimpleTreeNode3* node;
	if (parent.column() > 0) return 0;
	if (!parent.isValid())
	{
		node = root;
	}
	else
	{
		node = static_cast<SimpleTreeNode3*>(parent.internalPointer());
	}
	return node->childCount();
}

int SimpleTreeModel3::columnCount(const QModelIndex& index)const {
	if (index.isValid())
	{
		return static_cast<SimpleTreeNode3*>(index.internalPointer())->columnCount();
	}
	else
	{
		return root->columnCount();
	}
}

QVariant SimpleTreeModel3::data(const QModelIndex& index, int role)const {
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		SimpleTreeNode3* node = static_cast<SimpleTreeNode3*>(index.internalPointer());
		return node->checkState;
	}

	if (role == Qt::DisplayRole)
	{
		SimpleTreeNode3* node = static_cast<SimpleTreeNode3*>(index.internalPointer());
		return node->data(index.column());
	}
	return QVariant();
}

QVariant SimpleTreeModel3::headerData(int section, Qt::Orientation orientation, int role)const {
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return root->data(section);
	}
	return QVariant();
}

QModelIndex SimpleTreeModel3::index(int row, int column, const QModelIndex& parent)const {
	if (!hasIndex(row, column, parent)) return QModelIndex();

	SimpleTreeNode3* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<SimpleTreeNode3*>(parent.internalPointer());

	SimpleTreeNode3* child = p->child(row);
	if (child) return createIndex(row, column, child);
	else return QModelIndex();
}

QModelIndex SimpleTreeModel3::parent(const QModelIndex& index)const {
	if (!index.isValid()) return QModelIndex();

	SimpleTreeNode3* child = static_cast<SimpleTreeNode3*>(index.internalPointer());
	SimpleTreeNode3* parent = child->parent;
	if (parent == root) return QModelIndex();

	return createIndex(parent->row(), 0, parent);
}

bool SimpleTreeModel3::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		SimpleTreeNode3* node = static_cast<SimpleTreeNode3*>(index.internalPointer());
		Qt::CheckState state = qvariant_cast<Qt::CheckState>(value);
		if (state == Qt::Checked || state == Qt::Unchecked)
		{
			node->checkState = state;
			emit dataChanged(index, index);

			// 这两行不能颠倒顺序
			setDescendantsData(index, state);
			setAncestoresData(index, state);
		}
		
	}

	return true;
}

void SimpleTreeModel3::setDescendantsData(const QModelIndex& parent, Qt::CheckState state)
{
	SimpleTreeNode3* node = static_cast<SimpleTreeNode3*>(parent.internalPointer());
	if (node->hasChildren())
	{
		int count = rowCount(parent);
		for (int i = 0; i < count; i++)
		{
			QModelIndex child = index(i, 0, parent);
			node->child(i)->checkState = state;
			emit dataChanged(child, child);
			if (node->child(i)->hasChildren())
			{
				setDescendantsData(child, state);
			}
		}
	}
}

void SimpleTreeModel3::setAncestoresData(const QModelIndex& index, Qt::CheckState state)
{
	SimpleTreeNode3* node = static_cast<SimpleTreeNode3*>(index.internalPointer());
	SimpleTreeNode3* p = node->parent;
	QModelIndex idx = parent(index);
	while (p)
	{
		if (p->isCheckStateForValue(Qt::Checked)) p->checkState = Qt::Checked;
		else if (p->isCheckStateForValue(Qt::Unchecked)) p->checkState = Qt::Unchecked;
		else p->checkState = Qt::PartiallyChecked;
		emit dataChanged(idx, idx);

		idx = parent(idx);
		p = p->parent;
	}
}