#include "ZipFileTreeModel2.h"

#include <QFileInfo>
#include <QDebug>
#include "quazip/quazip.h"
#include "quazip/quazipdir.h"

ZipFileTreeModel2::ZipFileTreeModel2(const QString& path, QObject* parent) :
	QAbstractItemModel(parent),
	zipPath(path)
{
	root = new ZipFileTreeNode2(QString("/"));
	root->isDir = true;
	loadZip2(zipPath, root);
}

void ZipFileTreeModel2::loadZip(const QString& path, ZipFileTreeNode2* node)
{
	QuaZip zip(path);
	if (zip.open(QuaZip::mdUnzip))
	{
		QuaZipDir dir(&zip, "/");
		loadZip(dir, node);

	}
}

void ZipFileTreeModel2::loadZip2(const QString& apkPath, ZipFileTreeNode2* node)
{
	QuaZip zip(apkPath);
	if (zip.open(QuaZip::mdUnzip))
	{
		QString dirPath = node->fullPath();
		QuaZipDir dir(&zip, dirPath);
		QStringList names = dir.entryList();
		for (auto name : names)
		{
			ZipFileTreeNode2* child = new ZipFileTreeNode2(name, Qt::Unchecked, node);
			if (name.endsWith(QString("/")))
			{
				child->isDir = true;
				child->populatedChildren = false;
			}
			node->appendChild(child);
		}
		node->populatedChildren = true;
	}
}

void ZipFileTreeModel2::loadZip(QuaZipDir& dir, ZipFileTreeNode2* parent)
{
	QStringList names = dir.entryList();
	for (auto name : names)
	{
		ZipFileTreeNode2* node = new ZipFileTreeNode2(name, Qt::Unchecked, parent);
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

Qt::ItemFlags ZipFileTreeModel2::flags(const QModelIndex& index)const
{
	if (!index.isValid()) return 0;
	return QAbstractItemModel::flags(index);
}

int ZipFileTreeModel2::rowCount(const QModelIndex& parent)const
{
	ZipFileTreeNode2* p;
	if (parent.column() > 0) return 0;
	if (!parent.isValid()) p = root;
	else p = static_cast<ZipFileTreeNode2*>(parent.internalPointer());
	return p->childCount();
}

int ZipFileTreeModel2::columnCount(const QModelIndex& index)const {
	// 1 line
	return 1;
}

QVariant ZipFileTreeModel2::headerData(int section, Qt::Orientation orientation, int role)const
{
	return QVariant();
}

QVariant ZipFileTreeModel2::data(const QModelIndex& index, int role)const {
	if (!index.isValid()) return QVariant();
	if (role == Qt::DisplayRole)
	{
		ZipFileTreeNode2* node = static_cast<ZipFileTreeNode2*>(index.internalPointer());
		return node->filename;
	}
	else
	{
		return QVariant();
	}
}

QModelIndex ZipFileTreeModel2::index(int row, int column, const QModelIndex& parent)const {
	if (!hasIndex(row, column, parent)) return QModelIndex();

	ZipFileTreeNode2* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<ZipFileTreeNode2*>(parent.internalPointer());
	
	ZipFileTreeNode2* child = p->child(row);
	if (child) return createIndex(row, column, child);
	else return QModelIndex();
}

QModelIndex ZipFileTreeModel2::parent(const QModelIndex& index)const
{
	if (!index.isValid()) return QModelIndex();

	ZipFileTreeNode2* node = static_cast<ZipFileTreeNode2*>(index.internalPointer());
	ZipFileTreeNode2* p = node->parent;
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

bool ZipFileTreeModel2::hasChildren(const QModelIndex& parent)const
{
	if (parent.column() > 0) return false;

	ZipFileTreeNode2* node;
	if (!parent.isValid()) node = root;
	else node = static_cast<ZipFileTreeNode2*>(parent.internalPointer());
	return node->hasChidlren();
}

bool ZipFileTreeModel2::canFetchMore(const QModelIndex& parent)const
{
	ZipFileTreeNode2* node;
	if (!parent.isValid()) node = root;
	else node = static_cast<ZipFileTreeNode2*>(parent.internalPointer());

	if (node->isDir && (!node->populatedChildren))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ZipFileTreeModel2::fetchMore(const QModelIndex& parent)
{
	ZipFileTreeNode2* node = static_cast<ZipFileTreeNode2*>(parent.internalPointer());
	if (!node->populatedChildren)
	{
		loadZip2(this->zipPath, node);
		beginInsertRows(parent, 0, node->children.size());
		endInsertRows();
	}
}