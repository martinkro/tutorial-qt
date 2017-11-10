#ifndef NAMENUMBERINFORMATION_H
#define NAMENUMBERINFORMATION_H

#include <QString>
#include <QVariant>

#include "DataRow.h"

class NameNumberInfo : public DataRow
{
public:
	NameNumberInfo(const QString & name, const int & number, const int & minimum, const int & maximum)
		: name(name),
		number(number),
		minimum(minimum),
		maximum(maximum)
	{}

	QVariant GetData(int column) const override;

	int GetColumnCount() const override { return 2; }

	void DataChanged(const int & column, const QVariant & value) override;

	bool CanBeChanged(const int & column) const override;

	void SetEditorData(QWidget *editor, const int & column) const override;

	void SetDataFromEditor(QWidget * editor, int column) override;

private:
	const QString name;
	int number;
	const int maximum, minimum;
	static const int NAME_COLUMN = 0, NUMBER_COLUMN = 1;

	NameNumberInfo & operator=(NameNumberInfo & rhs) { return rhs; }
};

#endif // NAMENUMBERINFORMATION_H