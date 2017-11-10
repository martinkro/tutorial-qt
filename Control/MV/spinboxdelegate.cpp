#include "spinboxdelegate.h"
#include <QSpinBox>
#include <QtWidgets/QApplication>

SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

SpinBoxDelegate::~SpinBoxDelegate()
{
}

void SpinBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (index.column() == 0) {
		int progress = index.data().toInt();
		QStyleOptionProgressBar progressBarOption;
		progressBarOption.rect = option.rect;
		progressBarOption.minimum = 0;
		progressBarOption.maximum = 100;
		progressBarOption.progress = progress;
		progressBarOption.text = QString::number(progress) + "%";
		progressBarOption.textVisible = true;
		progressBarOption.textAlignment = Qt::AlignCenter;
		QApplication::style()->drawControl(QStyle::CE_ProgressBar,
			&progressBarOption, painter);
	}
	else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem & /* option */,
	const QModelIndex & /* index */) const
{
	QSpinBox *editor = new QSpinBox(parent);
	editor->setMinimum(0);
	editor->setMaximum(100);
	return editor;
}
void SpinBoxDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}
void SpinBoxDelegate::setModelData(QWidget *editor,
	QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	int value = spinBox->value();
	model->setData(index, value, Qt::EditRole);
}
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}


