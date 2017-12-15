#ifndef SIMPLE_TREE_MODEL2_H
#define SIMPLE_TREE_MODEL2_H

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>
#include <QPersistentModelIndex>

class SimpleTreeModel2:public QAbstractItemModel
{
    Q_OBJECT
public:
	class SimpleTreeNode2
	{
	public:
		SimpleTreeNode2(const QList<QVariant>& d, SimpleTreeNode2*p = nullptr) :
			value(d),
			parent(p)
		{

		}
		~SimpleTreeNode2()
		{
			qDeleteAll(children);
		}

	public:
		void appendChild(SimpleTreeNode2* node) { children.append(node); }
		SimpleTreeNode2* child(int row)const { return children.value(row); }
		int childCount()const { return children.size(); }
		int columnCount()const { return value.size(); }
		QVariant data(int column)const { return value.value(column); }
		int row()const
		{
			if (parent)
			{
				return parent->children.indexOf(const_cast<SimpleTreeNode2*>(this));
			}
			return 0;
		}

	public:
		QList<QVariant> value;
		SimpleTreeNode2* parent;
		QList<SimpleTreeNode2*> children;
	};
public:
    explicit SimpleTreeModel2(const QString& data,QObject* parent = Q_NULLPTR);
	virtual ~SimpleTreeModel2()
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
	void setupModel(const QStringList& lines,SimpleTreeNode2* p);

private:
	SimpleTreeNode2* root;
	QList<QPersistentModelIndex> checkedList;
};

#endif