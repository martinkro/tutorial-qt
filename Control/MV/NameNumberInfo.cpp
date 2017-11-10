#include "NameNumberInfo.h"
#include <QLineEdit>
#include <QSpinBox>

QVariant NameNumberInfo::GetData(int column) const
{
	switch (column)
	{
	case NAME_COLUMN:
		return name;

	case NUMBER_COLUMN:
		return number;

	default:
		return QVariant();
	}
}

void NameNumberInfo::DataChanged(const int & column, const QVariant & value)
{
	if (column == NUMBER_COLUMN)
		number = value.toInt();
}

bool NameNumberInfo::CanBeChanged(const int & column) const
{
	return column == NUMBER_COLUMN;
}

void NameNumberInfo::SetEditorData(QWidget *editor, const int & column) const
{
	switch (column)
	{
	case NAME_COLUMN:
	{
		QLineEdit * lineEdit = static_cast<QLineEdit *>(editor);
		lineEdit->setText(name);
		break;
	}

	case NUMBER_COLUMN:
	{
		QSpinBox * spinBox = static_cast<QSpinBox *>(editor);
		spinBox->setValue(number);
		spinBox->setMinimum(minimum);
		spinBox->setMaximum(maximum);
		break;
	}

	default:
		// Do nothing
		break;
	}
}

void NameNumberInfo::SetDataFromEditor(QWidget * editor, int column)
{
	switch (column)
	{
	case NAME_COLUMN:
	{
		QLineEdit * lineEdit = static_cast<QLineEdit *>(editor);
		DataChanged(column, lineEdit->text());
		break;
	}

	case NUMBER_COLUMN:
	{
		QSpinBox * spinBox = static_cast<QSpinBox *>(editor);
		DataChanged(column, spinBox->value());
		break;
	}
	}
}