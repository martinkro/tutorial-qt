#ifndef ZIP_FILE_TREE_MODEL2_H
#define ZIP_FILE_TREE_MODEL2_H

#include <QAbstractItemModel>

class QuaZipDir;
class ZipFileTreeModel2:public QAbstractItemModel
{
    Q_OBJECT
public:
	class ZipFileTreeNode2 {
	public:
		ZipFileTreeNode2(const QString& name, Qt::CheckState state = Qt::Unchecked, ZipFileTreeNode2* p = nullptr):
			checkState(state),
			filename(name),
			parent(p),
			populatedChildren(true),
			isDir(false)
		{
		}
		~ZipFileTreeNode2() {
			qDeleteAll(children);
		}

	public:
		int row()const {
			if (parent)
			{
				return parent->children.indexOf(const_cast<ZipFileTreeNode2*>(this));
			}
			return 0;
		}

		bool hasChidlren()const 
		{ 
			if ((!populatedChildren) && isDir) return true;
			return children.size() > 0; 
		}

		ZipFileTreeNode2* child(int row)const { return children.value(row); }
		void appendChild(ZipFileTreeNode2* node) { children.append(node); }
		int childCount()const { return children.size(); }

		QString fullPath()const {
			QString path = filename;
			ZipFileTreeNode2* temp = parent;
			while (temp)
			{
				path = temp->filename + path;
				temp = temp->parent;
			}
			return path;
		}
	public:
		Qt::CheckState checkState;
		QString filename;
		QList<ZipFileTreeNode2*> children;
		ZipFileTreeNode2* parent;
		bool populatedChildren; // 是否已经遍历了目录
		bool isDir;
	};
public:
    ZipFileTreeModel2(const QString& path,QObject* parent = Q_NULLPTR);
	virtual ~ZipFileTreeModel2()
	{
		delete root;
	}

public:
	QVariant data(const QModelIndex& index, int role)const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role)const override;
	
	int rowCount(const QModelIndex& index)const override;
	int columnCount(const QModelIndex& index)const override;

	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex())const override;
	QModelIndex parent(const QModelIndex& index)const override;

	Qt::ItemFlags flags(const QModelIndex& index)const override;

	bool hasChildren(const QModelIndex& parent = QModelIndex())const override;
	bool canFetchMore(const QModelIndex& parent = QModelIndex())const override;
	void fetchMore(const QModelIndex& parent = QModelIndex())override;


private:
	static void loadZip(const QString& path, ZipFileTreeNode2* node);
	static void loadZip(QuaZipDir& dir, ZipFileTreeNode2* node);
	void loadZip2(const QString& apkPath, ZipFileTreeNode2* node);
private:
	ZipFileTreeNode2* root;
	QString zipPath;
};


#endif