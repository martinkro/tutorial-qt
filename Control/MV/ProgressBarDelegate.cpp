#include "ProgressBarDelegate.h"

#include <QApplication>
#include <QDebug>
#include <QProgressBar>
#include <QPainter>
#include <QPushButton>
#include "gamelistitemview.h"

const int GAME_ICON_SIZE = 48;
const int GAME_LIST_PADDING = 2;
const int GAME_LIST_TEXT_LEFT_PADDING = 6;

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
		QRect rect = option.rect;
		//QListView* x = qobject_cast<QListView*>(parent());
		if (option.state & QStyle::State_Selected)
		{
			painter->fillRect(option.rect, option.palette.window());
		}

		QRect dst = rect;
		dst.setLeft(rect.left() + GAME_LIST_PADDING * 2 + GAME_ICON_SIZE + GAME_LIST_TEXT_LEFT_PADDING);
		dst.setTop(rect.top() + GAME_LIST_PADDING);
		dst.setBottom(dst.top() + GAME_ICON_SIZE/2);

		QFont fontTitle = painter->font();
		fontTitle.setBold(true);
		fontTitle.setPointSize(14);
		
		QPen titlePen = painter->pen();
		titlePen.setColor(Qt::red);   // text color
		// titlePen.setBrush(Qt::blue);

	   
		painter->save();
		painter->setFont(fontTitle);
		painter->setPen(titlePen);
		painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, "Name");
		painter->restore();

		dst = rect;
		dst.setLeft(rect.left() + GAME_LIST_PADDING * 2 + GAME_ICON_SIZE + GAME_LIST_TEXT_LEFT_PADDING);
		dst.setTop(rect.top() + GAME_LIST_PADDING + GAME_ICON_SIZE/2);
		dst.setBottom(dst.top() + GAME_ICON_SIZE / 2);
		painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, "123456987");

		dst = rect;
		dst.setRight(rect.left() + GAME_LIST_PADDING*2 + GAME_ICON_SIZE);
		QRect area(0, 0,GAME_ICON_SIZE,GAME_ICON_SIZE);
		area.moveCenter(dst.center());
		QPixmap pixmap("sgame.png");
		painter->drawPixmap(area, pixmap);

		
		return;
	}
	else if (index.column() == 0 && index.row() == 5)
	{
		if (option.state & QStyle::State_Selected)
		{
			painter->fillRect(option.rect, option.palette.highlight());
		}

		QRect rect = option.rect;
		int x = rect.x() + 2;
		int y = rect.y() + 2;
		QBrush brush;
		QPixmap pixmap("sgame.png");
		brush.setTexture(pixmap);
		painter->fillRect(x, y, 48, 48, brush);
		return;
	}
	else if (index.column() == 0 && index.row() == 6)
	{
		if (option.state & QStyle::State_Selected)
		{
			QColor background = option.palette.color(QPalette::Active, QPalette::Highlight);
			//QBrush brush(QPalette::Active, option.palette.highlight());
			painter->fillRect(option.rect, background);
		}
		else if (option.state & QStyle::State_MouseOver)
		{
			painter->fillRect(option.rect, option.palette.dark());
		}

		QRect rect = option.rect;
		int x = rect.x() + 2;
		int y = rect.y() + 2;
		QBrush brush;
		QPixmap pixmap("sgame.png");
		brush.setTexture(pixmap);
		painter->fillRect(x, y, 48, 48, brush);
		return;
	}
	else if (index.column() == 0 && index.row() == 2)
	{
		QStyleOptionButton opt;
		// opt.initFrom(this);
		opt.rect = option.rect;
		//opt.rect.adjust(2, 2, -4, -4);
		//opt.features = QStyleOptionButton::DefaultButton;
		//QWidget::State s = (State)(index.data(Qt::UserRole).toInt());
		//if (s == QWidget::Hovered)
		//	opt.state |= QStyle::State_MouseOver;
		//if (s == Pressed)
		//	opt.state |= QStyle::State_Sunken;
		opt.state = option.state;
		opt.palette = option.palette;
		opt.text = "QPushButton";
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
		size.setHeight(80);
		return size;
	}
	else if (index.column() == 0 && (index.row() == 1 || index.row()==5 || index.row()==6))
	{
		QSize size = option.rect.size();
		size.setHeight(GAME_ICON_SIZE + GAME_LIST_PADDING * 2);
		return size;
	}
	else if (index.column() == 0 && index.row() == 3)
	{
		QSize size = option.rect.size();
		size.setHeight(30);
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