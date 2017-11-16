#pragma once

#include <QAbstractTableModel>

class CurrencyModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CurrencyModel(QObject *parent = Q_NULLPTR);
	~CurrencyModel();
	void setCurrencyMap(const QMap<QString, double> &map);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole);
private:
	QString currencyAt(int offset) const;
	QMap<QString, double> currencyMap;
};