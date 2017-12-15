#ifndef ZIP_FILE_TREE_MODEL3_H
#define ZIP_FILE_TREE_MODEL3_H

#include <QAbstractItemModel>

class QuaZipDir;
class ZipFileTreeModel3:public QAbstractItemModel
{
    Q_OBJECT
public:
	class ZipFileTreeNode3 {
	public:
		ZipFileTreeNode3(const QString& name, Qt::CheckState state = Qt::Unchecked, ZipFileTreeNode3* p = nullptr):
			checkState(state),
			realCheckState(state),
			filename(name),
			parent(p),
			populatedChildren(true),
			isDir(false)
		{
		}
		~ZipFileTreeNode3() {
			qDeleteAll(children);
		}

	public:
		void setCheckState(Qt::CheckState state, bool real = false)
		{
			if (real) realCheckState = state;
			else checkState = state;
		}
		Qt::CheckState getCheckState(bool real = false)
		{
			if (real) return realCheckState;
			else return checkState;
		}
		void storeCheckState()
		{
			realCheckState = checkState;
			for (auto node : children)
			{
				node->storeCheckState();
			}
		}

		void restoreCheckState()
		{
			checkState = realCheckState;
			for (auto node : children)
			{
				node->restoreCheckState();
			}
		}
		int row()const {
			if (parent)
			{
				return parent->children.indexOf(const_cast<ZipFileTreeNode3*>(this));
			}
			return 0;
		}

		bool hasChildren()const 
		{ 
			if ((!populatedChildren) && isDir) return true;
			return children.size() > 0; 
		}

		void setCurrentNodeCheckState(const QStringList& verifyFileList, ZipFileTreeNode3* p, bool real = false)
		{
			setCheckState(p->getCheckState(real), real);
			if (p->getCheckState(real) == Qt::Checked)
			{
				setCheckState(Qt::Checked, real);
			}
			else if (p->getCheckState(real) == Qt::PartiallyChecked)
			{
				// 额外的逻辑，强耦合 以后改进
				setCheckState(Qt::Unchecked,real);
				for (auto item : verifyFileList)
				{
					if (item.compare(this->fullPath()) == 0)
					{
						setCheckState(Qt::Checked, real);
						break;
					}
					else if (this->hasChildren() && item.startsWith(this->fullPath()))
					{
						setCheckState(Qt::PartiallyChecked, real);
						break;
					}
					// 遍历整个校验文件列表
				}
			}
			else
			{
				setCheckState(Qt::Unchecked,real);
			}
		}

		// 当前状态与state是否一样
		bool isCheckStateForValue(Qt::CheckState state,bool real = false)
		{
			if (hasChildren())
			{
				bool result = true;
				for (auto item : children)
				{
					if (item->getCheckState(real) != state)
					{
						result = false;
						break;
					}
				}
				return result;
			}
			else
			{
				return state == getCheckState(real);
			}
			return false;
		}

		void fixNotLeafNodeCheckState(bool real = false)
		{
			// 只有处于半选状态的才需要修复
			if (hasChildren() && getCheckState(real) == Qt::PartiallyChecked)
			{
				int checkedCount = 0;
				int uncheckedCount = 0;
				int partiallyCheckedCount = 0;
				for (auto node : children)
				{
					node->fixNotLeafNodeCheckState(real);
					switch (node->getCheckState(real))
					{
					case Qt::Checked:
						checkedCount++;
						break;
					case Qt::Unchecked:
						uncheckedCount++;
						break;
					case Qt::PartiallyChecked:
						partiallyCheckedCount++;
						break;
					default:
						break;
					}
				}

				if (uncheckedCount == 0)
				{
					// 所有子节点都处于选中或者半选状态
					if (partiallyCheckedCount == 0)
					{
						setCheckState(Qt::Checked,real);
					}
					else
					{
						setCheckState(Qt::PartiallyChecked,real);
					}
				}
				else
				{
					// 有节点未选中
					if (checkedCount != 0 || partiallyCheckedCount != 0)
					{
						setCheckState(Qt::PartiallyChecked,real);
					}
					else
					{
						setCheckState(Qt::Unchecked,real);
					}
				}
			}
		}
		void updateCheckStateByFileName(const QString& filename,bool isRoot=false,bool real = false)
		{
			// 如果已经选中，不需要更新状态
			if (getCheckState(real) == Qt::Checked) return; 

			if (isRoot)
			{
				for (auto node : children)
				{
					node->updateCheckStateByFileName(filename,false,real);
				}
				return;
			}

			if (hasChildren())
			{
				if (filename.compare(this->fullPath()) == 0)
				{
					setCheckState(Qt::Checked,real);
				}
				else if (filename.startsWith(this->fullPath()))
				{
					setCheckState(Qt::PartiallyChecked,real);
					for (auto node : children)
					{
						node->updateCheckStateByFileName(filename,false,real);
					}
				}
				else
				{
					setCheckState(Qt::Unchecked, real);
				}
				
			}
			else
			{
				if (filename.compare(this->fullPath()) == 0)
				{
					setCheckState(Qt::Checked,real);
				}
				else
				{
					setCheckState(Qt::Unchecked, real);
				}
			}
		}

		ZipFileTreeNode3* child(int row)const { return children.value(row); }
		void appendChild(ZipFileTreeNode3* node) { children.append(node); }
		int childCount()const { return children.size(); }

		QString fullPath(){
			if (filepath.isEmpty())
			{
				QString path = filename;
				ZipFileTreeNode3* temp = parent;
				while (temp)
				{
					path = temp->filename + path;
					temp = temp->parent;
				}
				filepath = path;
			}
			return filepath;
		}

		Qt::CheckState getCheckState()const
		{
			return checkState;
		}
	public:
		Qt::CheckState checkState;
		Qt::CheckState realCheckState;
		QString filename;
		QString filepath;
		QList<ZipFileTreeNode3*> children;
		ZipFileTreeNode3* parent;
		bool populatedChildren; // 是否已经遍历了目录
		bool isDir;
	};
public:
    ZipFileTreeModel3(const QString& path,QObject* parent = Q_NULLPTR);
	virtual ~ZipFileTreeModel3()
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

	bool setData(const QModelIndex& index, const QVariant& value, int role)override;

public:
	void setVerifyFileList(const QStringList& list);

public slots:
	void storeData();
	void restoreData();
private:
		void setDescendantsData(const QModelIndex& parent, Qt::CheckState state);
		void setAncestoresData(const QModelIndex& index, Qt::CheckState state);
private:
	static void loadZip(const QString& path, ZipFileTreeNode3* node);
	static void loadZip(QuaZipDir& dir, ZipFileTreeNode3* node);
	void loadZip2(const QString& apkPath, ZipFileTreeNode3* node);
private:
	ZipFileTreeNode3* root;
	QString zipPath;
	QStringList verifyFileList;
};


#endif