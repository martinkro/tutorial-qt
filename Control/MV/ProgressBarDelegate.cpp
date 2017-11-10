#include "ProgressBarDelegate.h"

#include <QApplication>
#include <QDebug>
#include <QProgressBar>
#include <QPainter>
#include <QPushButton>
#include "gamelistitemview.h"

ProgressBarDelegate::ProgressBarDelegate( int column, QWidget* p )
	: QStyledItemDelegate( p )
	, m_column( column )
{
}

ProgressBarDelegate::~ProgressBarDelegate()
{
}

void ProgressBarDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if( index.column() == 0 && index.row()==0 ){
		// auto p = index.data().value<Progress>();
		//if( p.total > 0 )
		{
			// int percent = p.percent();
			int percent = index.data().toInt();

			QStyleOptionProgressBar progressBarOption;
			progressBarOption.initFrom( &m_bar );
			progressBarOption.rect = option.rect;
			progressBarOption.minimum = 0;
			progressBarOption.maximum = 100;
			progressBarOption.progress = percent;
			progressBarOption.text = QString::number( percent ) + "%";
			progressBarOption.textVisible = true;
			progressBarOption.textAlignment = Qt::AlignCenter;

			painter->save();
			QStyle *drawStyle = m_bar.style();
			drawStyle->drawControl( QStyle::CE_ProgressBar, &progressBarOption, painter, &m_bar );
			painter->restore();
			return;
		}
	}
	else if (index.column() == 0 && index.row() == 1)
	{
		//QListView* x = qobject_cast<QListView*>(parent());
		return;
	}
	else if (index.column() == 0 && index.row() == 2)
	{
		QStyleOptionButton opt;
		opt.rect = option.rect;
		opt.rect.adjust(4, 4, -8, -8);
		//opt.features = QStyleOptionButton::DefaultButton;
		//QWidget::State s = (State)(index.data(Qt::UserRole).toInt());
		//if (s == QWidget::Hovered)
		//	opt.state |= QStyle::State_MouseOver;
		//if (s == Pressed)
		//	opt.state |= QStyle::State_Sunken;
		opt.state |= QStyle::State_Enabled;
		opt.text = "View Button";
		QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
		return;
	}
	else if (index.column() == 0 && index.row() == 3)
	{
		QAbstractItemView* x = qobject_cast<QAbstractItemView*>(parent());
		QPushButton* btn = new QPushButton("QPushButton", x);
		QPixmap map = QPixmap::grabWidget(btn);
		painter->drawPixmap(option.rect.x(), option.rect.y(), map);
		return;
	}
	else if (index.column() == 0 && index.row() == 4)
	{
		QAbstractItemView* x = qobject_cast<QAbstractItemView*>(parent());
		GameListItemView* btn = new GameListItemView(x);
		QPixmap map = QPixmap::grabWidget(btn);
		painter->drawPixmap(option.rect.x(), option.rect.y(), map);
		return;
	}
	
	QStyledItemDelegate::paint( painter, option, index );
}

QSize ProgressBarDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (index.column() == 0 && index.row() == 4)
	{
		QSize size = option.rect.size();
		size.setHeight(65);
		return size;
	}
	else if (index.column() == 0 && index.row() == 1)
	{
		QSize size = option.rect.size();
		size.setHeight(20);
		return size;
	}
	else if (index.column() == 0 && index.row() == 2)
	{
		QSize size = option.rect.size();
		size.setHeight(40);
		return size;
	}
	return QStyledItemDelegate::sizeHint(option, index);
}

void ProgressBarDelegate::initItem( QTreeWidgetItem* item, int column, int total )
{
	QVariant v;
	v.setValue<Progress>( Progress( 0, total ) );
	item->setData( column, Qt::DisplayRole, v );
}

bool ProgressBarDelegate::setItem( QTreeWidgetItem* item, int column, int progress )
{
	auto v = item->data( column, Qt::DisplayRole );
	auto p = v.value<Progress>();

	p.progress = progress;
	if( p.progress > p.total ){
		p.progress = p.total;
	}
	v.setValue<Progress>( p );
	item->setData( column, Qt::DisplayRole, v );
	return p.isFinished();
}