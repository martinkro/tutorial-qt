#ifndef SIMPLE_TREE_MODEL3_H
#define SIMPLE_TREE_MODEL3_H

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>

class SimpleTreeModel3:public QAbstractItemModel
{
    Q_OBJECT
public:
	class SimpleTreeNode3
	{
	public:
		SimpleTreeNode3(const QList<QVariant>& d, SimpleTreeNode3*p = nullptr) :
			value(d),
			parent(p),
			checkState(Qt::Unchecked)
		{

		}
		~SimpleTreeNode3()
		{
			qDeleteAll(children);
		}

	public:
		bool hasChildren()const
		{
			return children.size() > 0;
		}

		// 当前状态与state是否一样
		bool isCheckStateForValue(Qt::CheckState state)
		{
			if (hasChildren())
			{
				bool result = true;
				for (auto item : children)
				{
					if (item->checkState != state)
					{
						result = false;
						break;
					}
				}
				return result;
			}
			else
			{
				return state == checkState;
			}
			return false;
		}
		void appendChild(SimpleTreeNode3* node) { children.append(node); }
		SimpleTreeNode3* child(int row)const { return children.value(row); }
		int childCount()const { return children.size(); }
		int columnCount()const { return value.size(); }
		QVariant data(int column)const { return value.value(column); }
		int row()const
		{
			if (parent)
			{
				return parent->children.indexOf(const_cast<SimpleTreeNode3*>(this));
			}
			return 0;
		}

	public:
		QList<QVariant> value;
		SimpleTreeNode3* parent;
		QList<SimpleTreeNode3*> children;
		Qt::CheckState checkState;
	};
public:
    explicit SimpleTreeModel3(const QString& data,QObject* parent = Q_NULLPTR);
	virtual ~SimpleTreeModel3()
	{
		delete root;
	}

	QVariant data(const QModelIndex& index, int role)const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role)const override;

	int rowCount(const QModelIndex& parent = QModelIndex())const override;
	int columnCount(const QModelIndex& parent = QModelIndex())const override;

	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex())const override;
	QModelIndex parent(const QModelIndex& index)const override;

	Qt::ItemFlags flags(const QModelIndex& index)const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role)override;

private:
	void setDescendantsData(const QModelIndex& index,Qt::CheckState state);
	void setAncestoresData(const QModelIndex& index, Qt::CheckState state);
private:
	void setupModel(const QStringList& lines,SimpleTreeNode3* p);

private:
	SimpleTreeNode3* root;

};

#endif