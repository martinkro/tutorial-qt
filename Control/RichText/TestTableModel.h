#ifndef ENCRYPT_FILE_TABLE_MODEL_H
#define ENCRYPT_FILE_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
struct EncryptFileItem
{
    QString filename;
    Qt::CheckState checked;
	Qt::CheckState realChecked;
};

class EncryptFileTableModel:public QAbstractTableModel
{
    Q_OBJECT
public:
    EncryptFileTableModel(QObject* parent);
	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);
	Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetDataSet(const QList<EncryptFileItem>& data)
    {
		beginResetModel();
        dataSet = data;
		endResetModel();
		isDirty = false;
    }

	void saveData();
	void restoreData();

private:
    QList<EncryptFileItem> dataSet;
	bool isDirty;
};

#endif