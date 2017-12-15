#include "SimpleTreeModel.h"

SimpleTreeModel::SimpleTreeModel(const QString& data, QObject* parent) :
	QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Title" << "Summary";
	root = new SimpleTreeNode(rootData);
	setupModel(data.split(QString("\n")), root);
}

void SimpleTreeModel::setupModel(const QStringList& lines, SimpleTreeNode* p)
{
	// ·ÇµÝ¹é½âÎö
	QList<SimpleTreeNode*> parents;
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
			parents.last()->appendChild(new SimpleTreeNode(columnData, parents.last()));
		}

		++number;
	}
}

Qt::ItemFlags SimpleTreeModel::flags(const QModelIndex& index)const {
	if (!index.isValid()) return 0;
	return QAbstractItemModel::flags(index);
}

int SimpleTreeModel::rowCount(const QModelIndex& parent)const
{
	SimpleTreeNode* node;
	if (parent.column() > 0) return 0;
	if (!parent.isValid())
	{
		node = root;
	}
	else
	{
		node = static_cast<SimpleTreeNode*>(parent.internalPointer());
	}
	return node->childCount();
}

int SimpleTreeModel::columnCount(const QModelIndex& index)const {
	if (index.isValid())
	{
		return static_cast<SimpleTreeNode*>(index.internalPointer())->columnCount();
	}
	else
	{
		return root->columnCount();
	}
}

QVariant SimpleTreeModel::data(const QModelIndex& index, int role)const {
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)
	{
		SimpleTreeNode* node = static_cast<SimpleTreeNode*>(index.internalPointer());
		return node->data(index.column());
	}
	return QVariant();
}

QVariant SimpleTreeModel::headerData(int section, Qt::Orientation orientation, int role)const {
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return root->data(section);
	}
	return QVariant();
}

QModelIndex SimpleTreeModel::index(int row, int column, const QModelIndex& parent)const {
	if (!hasIndex(row, column, parent)) return QModelIndex();

	SimpleTreeNode* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<SimpleTreeNode*>(parent.internalPointer());

	SimpleTreeNode* child = p->child(row);
	if (child) return createIndex(row, column, child);
	else return QModelIndex();
}

QModelIndex SimpleTreeModel::parent(const QModelIndex& index)const {
	if (!index.isValid()) return QModelIndex();

	SimpleTreeNode* child = static_cast<SimpleTreeNode*>(index.internalPointer());
	SimpleTreeNode* parent = child->parent;
	if (parent == root) return QModelIndex();

	return createIndex(parent->row(), 0, parent);
}