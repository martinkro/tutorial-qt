#ifndef SIMPLE_TREE_MODEL_H
#define SIMPLE_TREE_MODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>

class SimpleTreeModel:public QAbstractItemModel
{
    Q_OBJECT
public:
	class SimpleTreeNode
	{
	public:
		SimpleTreeNode(const QList<QVariant>& d, SimpleTreeNode*p = nullptr) :
			value(d),
			parent(p)
		{

		}
		~SimpleTreeNode()
		{
			qDeleteAll(children);
		}

	public:
		void appendChild(SimpleTreeNode* node) { children.append(node); }
		SimpleTreeNode* child(int row)const { return children.value(row); }
		int childCount()const { return children.size(); }
		int columnCount()const { return value.size(); }
		QVariant data(int column)const { return value.value(column); }
		int row()const
		{
			if (parent)
			{
				return parent->children.indexOf(const_cast<SimpleTreeNode*>(this));
			}
			return 0;
		}

	public:
		QList<QVariant> value;
		SimpleTreeNode* parent;
		QList<SimpleTreeNode*> children;
	};
public:
    explicit SimpleTreeModel(const QString& data,QObject* parent = Q_NULLPTR);
	virtual ~SimpleTreeModel()
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

private:
	void setupModel(const QStringList& lines,SimpleTreeNode* p);

private:
	SimpleTreeNode* root;

};

#endif