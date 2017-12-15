#include "XJsonModel.h"
#include <QIODevice>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

XJsonModel::XJsonModel(QObject* parent) :
	QAbstractItemModel(parent),
	root(new XJsonNode()),
	document(),
	headers(QStringList() << "Key" << "Value")
{

}

XJsonModel::~XJsonModel()
{
	delete root;
}

XJsonModel::XJsonNode* XJsonModel::loadJsonValue(const QJsonValue& value, XJsonNode* p)
{
	XJsonNode* root = new XJsonNode(p);
	root->key = "root";
	if (value.isObject())
	{
		for (QString key : value.toObject().keys())
		{
			QJsonValue v = value.toObject().value(key);
			XJsonNode* node = loadJsonValue(v, root);
			node->key = key;
			node->type = v.type();
			root->appendChild(node);
		}
	}
	else if (value.isArray())
	{
		int index = 0;
		for (QJsonValue v : value.toArray())
		{
			XJsonNode* node = loadJsonValue(v, root);
			node->key = QString::number(index);
			node->type = v.type();
			root->appendChild(node);
			++index;
		}
	}
	else
	{
		root->value = value.toVariant().toString();
		root->type = value.type();
	}
	return root;
}

bool XJsonModel::load(const QString& filename)
{
	QFile file(filename);
	bool success = false;
	if (file.open(QIODevice::ReadOnly))
	{
		success = load(&file);
		file.close();
	}
	else
	{
		success = false;
	}
	return success;
}

bool XJsonModel::load(QIODevice* device)
{
	return loadJson(device->readAll());
}

bool XJsonModel::loadJson(const QByteArray& json)
{
	document = QJsonDocument::fromJson(json);
	if (!document.isNull())
	{
		beginResetModel();
		delete root;
		if (document.isArray())
		{
			root = loadJsonValue(QJsonValue(document.array()));
		}
		else
		{
			root = loadJsonValue(QJsonValue(document.object()));
		}
		endResetModel();
		return true;
	}
	return false;
}

// override function
QVariant XJsonModel::data(const QModelIndex& index, int role)const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	XJsonNode* node = static_cast<XJsonNode*>(index.internalPointer());
	if (role == Qt::DisplayRole)
	{
		if (index.column() == 0)
			return QString("%1").arg(node->key);
		if (index.column() == 1)
			return QString("%1").arg(node->value);
	}
	return QVariant();
}

QVariant XJsonModel::headerData(int section, Qt::Orientation orientation, int role)const
{
	if (role != Qt::DisplayRole) return QVariant();
	if (orientation == Qt::Horizontal)
	{
		return headers.value(section);
	}
	return QVariant();
}

int XJsonModel::rowCount(const QModelIndex& parent)const
{
	XJsonNode* p;
	if (parent.column() > 0) return 0;
	if (!parent.isValid())
	{
		p = root;
	}
	else
	{
		p = static_cast<XJsonNode*>(parent.internalPointer());
	}
	return p->count();
}

int XJsonModel::columnCount(const QModelIndex& parent)const 
{
	Q_UNUSED(parent);
	return 2;
}

QModelIndex XJsonModel::index(int row, int column, const QModelIndex& parent)const 
{
	if (!hasIndex(row, column, parent)) return QModelIndex();

	XJsonNode* p;
	if (!parent.isValid()) p = root;
	else p = static_cast<XJsonNode*>(parent.internalPointer());

	XJsonNode* node = p->child(row);
	if (node) return createIndex(row, column, node);
	else return QModelIndex();
	
}

QModelIndex XJsonModel::parent(const QModelIndex& index)const 
{
	if (!index.isValid()) return QModelIndex();

	XJsonNode* node = static_cast<XJsonNode*>(index.internalPointer());
	XJsonNode* p = node->parent;
	if (p == this->root) return QModelIndex();

	return createIndex(p->row(), 0, p);
}

