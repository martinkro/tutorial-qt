#ifndef ZIP_FILE_TREE_MODEL_H
#define ZIP_FILE_TREE_MODEL_H

#include <QAbstractItemModel>

class QuaZipDir;
class ZipFileTreeModel:public QAbstractItemModel
{
    Q_OBJECT
public:
	class ZipFileTreeNode {
	public:
		ZipFileTreeNode(const QString& name, Qt::CheckState state = Qt::Unchecked, ZipFileTreeNode* p = nullptr):
			checkState(state),
			filename(name),
			parent(p){}
		~ZipFileTreeNode() {
			qDeleteAll(children);
		}

	public:
		int row()const {
			if (parent)
			{
				return parent->children.indexOf(const_cast<ZipFileTreeNode*>(this));
			}
			return 0;
		}

		bool isDir()const { return children.size() > 0; }

		ZipFileTreeNode* child(int row)const { return children.value(row); }
		void appendChild(ZipFileTreeNode* node) { children.append(node); }
		int childCount()const { return children.size(); }
	public:
		Qt::CheckState checkState;
		QString filename;
		QList<ZipFileTreeNode*> children;
		ZipFileTreeNode* parent;
	};
public:
    ZipFileTreeModel(const QString& path,QObject* parent = Q_NULLPTR);
	virtual ~ZipFileTreeModel()
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


private:
	static void loadZip(const QString& path, ZipFileTreeNode* node);
	static void loadZip(QuaZipDir& dir, ZipFileTreeNode* node);
private:
	ZipFileTreeNode* root;
	QString zipPath;
};


#endif