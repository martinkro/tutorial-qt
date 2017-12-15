#include "ZipFileTreeModel3.h"

#include <QFileInfo>
#include <QDebug>
#include "quazip/quazip.h"
#include "quazip/quazipdir.h"

ZipFileTreeModel3::ZipFileTreeModel3(const QString& path, QObject* parent) :
	QAbstractItemModel(parent),
	zipPath(path)
{
	root = new ZipFileTreeNode3(QString(""));
	root->isDir = true;
	loadZip2(zipPath, root);
}

void ZipFileTreeModel3::loadZip(const QString& path, ZipFileTreeNode3* node)
{
	QuaZip zip(path);
	if (zip.open(QuaZip::mdUnzip))
	{
		QuaZipDir dir(&zip, "/");
		loadZip(dir, node);

	}
}

void ZipFileTreeModel3::loadZip2(const QString& apkPath, ZipFileTreeNode3* node)
{
	QuaZip zip(apkPath);
	if (zip.open(QuaZip::mdUnzip))
	{
		QString dirPath = node->fullPath();
		QuaZipDir dir(&zip, dirPath);
		QStringList names = dir.entryList();
		for (auto name : names)
		{
			ZipFileTreeNode3* child = new ZipFileTreeNode3(name, Qt::Unchecked, node);
			if (name.endsWith(QString("/")))
			{
				child->isDir = true;
				child->populatedChildren = false;
			}
			child->setCurrentNodeCheckState(verifyFileList, node, false);
			child->setCurrentNodeCheckState(verifyFileList, node, true);
			node->appendChild(child);
		}
		node->populatedChildren = true;
		// 需要修复节点状态?
		node->fixNotLeafNodeCheckState(false);
		node->fixNotLeafNodeCheckState(true);
	}
}

void ZipFileTreeModel3::loadZip(QuaZipDir& dir, ZipFileTreeNode3* parent)
{
	QStringList names = dir.entryList();
	for (auto name : names)
	{
		ZipFileTreeNode3* node = new ZipFileTreeNode3(name, Qt::Unchecked, parent);
		if (name.endsWith(QString("")))
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

Qt::ItemFlags ZipFileTreeModel3::flags(const QModelIndex& index)const
{
	if (!index.isValid()) return 0;
	if (index.column() == 0) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
	return QAbstractItemModel::flags(index);
}

int ZipFileTreeModel3::rowCount(const QModelIndex& parent)const
{
	ZipFileTreeNode3* p;
	if (parent.column() > 0) return 0;
	if (!parent.isValid()) p = root;
	else p = static_cast<ZipFileTreeNode3*>(parent.internalPointer());
	return p->childCount();
}

int ZipFileTreeModel3::columnCount(const QModelIndex& index)const {
	// 1 line
	return 1;
}

QVariant ZipFileTreeModel3::headerData(int section, Qt::Orientation orientation, int role)const
{
	return QVariant();
}

QVariant ZipFileTreeModel3::data(const QModelIndex& index, int role)const {
	if (!index.isValid()) return QVariant();
	if (role == Qt::DisplayRole)
	{
		ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(index.internalPointer());
		return node->filename;
	}
	else if (role == Qt::CheckStateRole && index.column() == 0)
	{
		ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(index.internalPointer());
		return node->getCheckState();
	}
	else
	{
		return QVariant();
	}
}

QModelIndex ZipFileTreeModel3::index(int row, int column, const QModelIndex& parent)const {
	if (!hasIndex(row, column, parent)) return QModelIndex();

	ZipFileTreeNode3* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<ZipFileTreeNode3*>(parent.internalPointer());
	
	ZipFileTreeNode3* child = p->child(row);
	if (child) return createIndex(row, column, child);
	else return QModelIndex();
}

QModelIndex ZipFileTreeModel3::parent(const QModelIndex& index)const
{
	if (!index.isValid()) return QModelIndex();

	ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(index.internalPointer());
	ZipFileTreeNode3* p = node->parent;
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

bool ZipFileTreeModel3::hasChildren(const QModelIndex& parent)const
{
	if (parent.column() > 0) return false;

	ZipFileTreeNode3* node;
	if (!parent.isValid()) node = root;
	else node = static_cast<ZipFileTreeNode3*>(parent.internalPointer());
	return node->hasChildren();
}

bool ZipFileTreeModel3::canFetchMore(const QModelIndex& parent)const
{
	ZipFileTreeNode3* node;
	if (!parent.isValid()) node = root;
	else node = static_cast<ZipFileTreeNode3*>(parent.internalPointer());

	if (node->isDir && (!node->populatedChildren))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ZipFileTreeModel3::fetchMore(const QModelIndex& parent)
{
	ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(parent.internalPointer());
	if (!node->populatedChildren)
	{
		loadZip2(this->zipPath, node);
		beginInsertRows(parent, 0, node->children.size());
		endInsertRows();
	}
}

bool ZipFileTreeModel3::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::CheckStateRole && index.column() == 0)
	{
		ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(index.internalPointer());
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


void ZipFileTreeModel3::setDescendantsData(const QModelIndex& parent, Qt::CheckState state)
{
	ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(parent.internalPointer());
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

void ZipFileTreeModel3::setAncestoresData(const QModelIndex& index, Qt::CheckState state)
{
	ZipFileTreeNode3* node = static_cast<ZipFileTreeNode3*>(index.internalPointer());
	ZipFileTreeNode3* p = node->parent;
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

void ZipFileTreeModel3::storeData()
{
	root->storeCheckState();
}

void ZipFileTreeModel3::restoreData()
{
	root->restoreCheckState();
}

void ZipFileTreeModel3::setVerifyFileList(const QStringList& list)
{
	verifyFileList = list;
	for (auto name : verifyFileList)
	{
		root->updateCheckStateByFileName(name,true,false);
		root->updateCheckStateByFileName(name, true, true);
	}

	// 处理完成后，需要清理一遍
	root->fixNotLeafNodeCheckState(false);
	root->fixNotLeafNodeCheckState(true);
}