#ifndef XJSONMODEL_H
#define XJSONMODEL_H

#include <QAbstractItemModel>
#include <QJsonValue>
#include <QJsonDocument>

class QIODevice;

class XJsonModel:public QAbstractItemModel
{
    Q_OBJECT
public:
	class XJsonNode
	{
	public:
		XJsonNode(XJsonNode* p = nullptr) :
			parent(p)
		{

		}
		~XJsonNode()
		{
			qDeleteAll(this->children);
			this->parent = nullptr;
		}
		void appendChild(XJsonNode* node) { this->children.append(node); }
		XJsonNode* child(int row) { return this->children.value(row); }
		int count() const { return this->children.size(); }
		int row() const {
			if (parent)
			{
				return parent->children.indexOf(const_cast<XJsonNode*>(this));
			}
			return 0;
		}


	public:
		QString key;
		QString value;
		QJsonValue::Type type;
		QList<XJsonNode*> children;
		XJsonNode* parent;
	};
public:
    explicit XJsonModel(QObject* parent = Q_NULLPTR);
	~XJsonModel();

public:
	bool load(const QString& filename);
	bool load(QIODevice* device);
	bool loadJson(const QByteArray& json);

public:
	QVariant data(const QModelIndex& index, int role)const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation, int role)const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex())const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex& index)const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex& parent = QModelIndex())const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex& parent = QModelIndex())const Q_DECL_OVERRIDE;

public:
	static XJsonNode* loadJsonValue(const QJsonValue& v, XJsonNode*p = 0);

private:
	XJsonNode* root;
	QJsonDocument document;
	QStringList headers;
};


#endif