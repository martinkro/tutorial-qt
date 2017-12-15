#include "ZipFileTreeModel.h"

#include <QFileInfo>
#include <QDebug>
#include "quazip/quazip.h"
#include "quazip/quazipdir.h"

ZipFileTreeModel::ZipFileTreeModel(const QString& path, QObject* parent) :
	QAbstractItemModel(parent),
	zipPath(path)
{
	root = new ZipFileTreeNode(QFileInfo(zipPath).fileName());
	loadZip(zipPath, root);
}

void ZipFileTreeModel::loadZip(const QString& path, ZipFileTreeNode* node)
{
	QuaZip zip(path);
	if (zip.open(QuaZip::mdUnzip))
	{
		QuaZipDir dir(&zip, "/");
		loadZip(dir, node);

	}
}

void ZipFileTreeModel::loadZip(QuaZipDir& dir, ZipFileTreeNode* parent)
{
	QStringList names = dir.entryList();
	for (auto name : names)
	{
		ZipFileTreeNode* node = new ZipFileTreeNode(name, Qt::Unchecked, parent);
		if (name.endsWith(QString("/")))
		{
			// dir
			if (dir.cd(name))
			{
				loadZip(dir, node);
				dir.cdUp();
			}
			
		}
		parent->appendChild(node);
	}
}

Qt::ItemFlags ZipFileTreeModel::flags(const QModelIndex& index)const
{
	if (!index.isValid()) return 0;
	return QAbstractItemModel::flags(index);
}

int ZipFileTreeModel::rowCount(const QModelIndex& parent)const
{
	ZipFileTreeNode* p;
	if (parent.column() > 0) return 0;
	if (!parent.isValid()) p = root;
	else p = static_cast<ZipFileTreeNode*>(parent.internalPointer());
	return p->childCount();
}

int ZipFileTreeModel::columnCount(const QModelIndex& index)const {
	// 1 line
	return 1;
}

QVariant ZipFileTreeModel::headerData(int section, Qt::Orientation orientation, int role)const
{
	return QVariant();
}

QVariant ZipFileTreeModel::data(const QModelIndex& index, int role)const {
	if (!index.isValid()) return QVariant();
	if (role == Qt::DisplayRole)
	{
		ZipFileTreeNode* node = static_cast<ZipFileTreeNode*>(index.internalPointer());
		return node->filename;
	}
	else
	{
		return QVariant();
	}
}

QModelIndex ZipFileTreeModel::index(int row, int column, const QModelIndex& parent)const {
	if (!hasIndex(row, column, parent)) return QModelIndex();

	ZipFileTreeNode* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<ZipFileTreeNode*>(parent.internalPointer());
	
	ZipFileTreeNode* child = p->child(row);
	if (child) return createIndex(row, column, child);
	else return QModelIndex();
}

QModelIndex ZipFileTreeModel::parent(const QModelIndex& index)const
{
	if (!index.isValid()) return QModelIndex();

	ZipFileTreeNode* node = static_cast<ZipFileTreeNode*>(index.internalPointer());
	ZipFileTreeNode* p = node->parent;
	if (p == root) return QModelIndex();

	
	if (p)
	{
		return createIndex(p->row(), 0, p);
	}
	else
	{
		qDebug() << "Warning parent is nullptr";
		return QModelIndex();
	}
}