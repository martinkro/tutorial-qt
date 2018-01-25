#include "ProgressBarDelegate.h"

#include <QApplication>
#include <QDebug>
#include <QProgressBar>
#include <QPainter>
#include <QPushButton>
#include "gamelistitemview.h"

#include <QDebug>

const int GAME_ICON_SIZE = 48;
const int GAME_LIST_PADDING = 2;
const int GAME_LIST_TEXT_LEFT_PADDING = 6;

ProgressBarDelegate::ProgressBarDelegate( int column, QWidget* p )
	: QStyledItemDelegate( p )
	, m_column( column )
{
    m_bar.setObjectName("cell_pack_upload");
}

ProgressBarDelegate::~ProgressBarDelegate()
{
}

void ProgressBarDelegate::paintProgressBar1(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    int percent = index.data().toInt();

    QStyleOptionProgressBar progressBarOption;
    progressBarOption.initFrom(&m_bar);
    QRect area(0, 0, 86, option.rect.height() - 2);
    area.moveCenter(option.rect.center());
    progressBarOption.rect = area;
    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.progress = percent;
    //progressBarOption.text = QString::number( percent ) + "%";
    progressBarOption.text = tr("download %1%").arg(QString::number(percent));
    progressBarOption.textVisible = true;
    progressBarOption.textAlignment = Qt::AlignCenter;

    painter->save();
    QFont textFont = painter->font();
    textFont.setPixelSize(12);
    //QPen textPen = painter->pen();
    //textPen.setColor(color);
    //painter->setPen(textPen);
    //painter->setFont(textFont);
    qApp->style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    painter->restore();
}
void ProgressBarDelegate::paintProgressBar2(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    int percent = index.data().toInt();

    QStyleOptionProgressBar progressBarOption;
    progressBarOption.initFrom(&m_bar);
    QRect area(0, 0, 86, option.rect.height() - 2);
    area.moveCenter(option.rect.center());
    progressBarOption.rect = area;
    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.progress = percent;
    //progressBarOption.text = QString::number( percent ) + "%";
    progressBarOption.text = tr("upload %1%").arg(QString::number(percent));
    progressBarOption.textVisible = true;
    progressBarOption.textAlignment = Qt::AlignCenter;

    painter->save();
    QStyle *drawStyle = m_bar.style();
    drawStyle->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, &m_bar);
    painter->restore();
}

void ProgressBarDelegate::paintProgressBar3(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    int percent = index.data().toInt();

    QRect area(0, 0, 86, option.rect.height() - 2);
    area.moveCenter(option.rect.center());
    QString text = tr("upload %1%").arg(QString::number(percent));

    QPixmap pixmapMemory(area.width(), area.height());
    pixmapMemory.fill(Qt::transparent);
    QPainter painterMemory(&pixmapMemory);
    painterMemory.setRenderHint(QPainter::Antialiasing, true);
    //painterMemory.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painterMemory.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painterMemory.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painterMemory.setCompositionMode(QPainter::CompositionMode_Source);
    painterMemory.setCompositionMode(QPainter::CompositionMode_Destination);
    painterMemory.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painterMemory.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painterMemory.setCompositionMode(QPainter::CompositionMode_SourceOut);        // ok
    painterMemory.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    painterMemory.setCompositionMode(QPainter::CompositionMode_Xor);    // ok
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Plus);
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Multiply);
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Xor);
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Xor);
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Xor);
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Xor);
    //painterMemory.setCompositionMode(QPainter::CompositionMode_Xor);

    QRect rectMemory(0, 0, area.width(), area.height());

    


    // draw text
    QColor color(0x4886ff);
    painterMemory.save();
    QFont textFont = painter->font();
    textFont.setPixelSize(12);
    QPen textPen = painter->pen();
    textPen.setColor(color);
    painterMemory.setPen(textPen);
    painterMemory.setFont(textFont);
    painterMemory.drawText(rectMemory, Qt::AlignCenter, text);
    painterMemory.restore();

    // chunk
    QColor brushColor(0x85b1e3);
    painterMemory.save();
    //QPen pen(color, 1);
    //painter->setPen(pen);
    QRect rectBackground = rectMemory;
    rectBackground.setWidth(area.width() * percent / 100);
    painterMemory.fillRect(rectBackground, brushColor);
    painterMemory.restore();

    painter->drawPixmap(area, pixmapMemory);
    //QColor brushColor(0x85b1e3);
    //painter->save();
    ////QPen pen(color, 1);
    ////painter->setPen(pen);
    //QRect rectBackground = area;
    //rectBackground.setWidth(area.width() * percent / 100);
    //painter->fillRect(rectBackground, brushColor);
    //painter->restore();

    //// 85b1e3
    //QColor color(0x4886ff);
    //painter->save();
    //QFont textFont = painter->font();
    //textFont.setPixelSize(12);
    //QPen textPen = painter->pen();
    //textPen.setColor(color);
    //painter->setPen(textPen);
    //painter->setFont(textFont);
    //painter->drawText(area, Qt::AlignCenter, text);
    //painter->restore();

    
}

void ProgressBarDelegate::paintButton1(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    static QStringList texts = { tr("cancel"), tr("download"), tr("browser") };
    QColor color(Qt::red);
    QRect area(0, 0, 51, 28);
    area.moveCenter(option.rect.center());
    qDebug() << option.state;
    qDebug() << QString::number(option.state, 16);
    qDebug() << option.checkState;
    // ±³¾°
    if (option.state.testFlag(QStyle::State_HasFocus) 
        && option.state.testFlag(QStyle::State_MouseOver) 
        && option.state.testFlag(QStyle::State_Enabled))
    {
        qDebug() << "1:" << option.state;
        qDebug() << "1:" << option.checkState;
        painter->save();
        //painter->fillRect(area, QColor(0xe75252));
        painter->fillRect(area, QColor(Qt::green));
        painter->restore();

        color = QColor(Qt::white);
        painter->save();
        QFont textFont = painter->font();
        textFont.setPixelSize(12);
        QPen textPen = painter->pen();
        textPen.setColor(color);
        painter->setPen(textPen);
        painter->setFont(textFont);
        painter->drawText(area, Qt::AlignCenter, texts.at((index.row() % 3)));
        painter->restore();
    }
    else if (option.state.testFlag(QStyle::State_MouseOver))
    {
        qDebug() << "2:" << option.state;
        qDebug() << "2:" << option.checkState;
        painter->save();
        //painter->fillRect(area, QColor(0xf06060));
        painter->setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addRoundedRect(area, 1, 1);
        QPen pen(QColor(0xf06060), 1);
        painter->setPen(pen);
        painter->fillPath(path, QColor(0xf06060));
        painter->drawPath(path);

        painter->restore();

        color = QColor(Qt::white);
        painter->save();
        QFont textFont = painter->font();
        textFont.setPixelSize(12);
        QPen textPen = painter->pen();
        textPen.setColor(color);
        painter->setPen(textPen);
        painter->setFont(textFont);
        painter->drawText(area, Qt::AlignCenter, texts.at((index.row() % 3)));
        painter->restore();
    }
    else
    {
        qDebug() << "3:" << option.state;
        qDebug() << "3:" << option.checkState;
        painter->save();
        QPen pen(color, 1);
        painter->setPen(pen);
        painter->drawRoundedRect(area, 1, 1);
        painter->restore();

        painter->save();
        QFont textFont = painter->font();
        textFont.setPixelSize(12);
        QPen textPen = painter->pen();
        textPen.setColor(color);
        painter->setPen(textPen);
        painter->setFont(textFont);
        painter->drawText(area, Qt::AlignCenter, texts.at((index.row() % 3)));
        painter->restore();
    }
    
}
void ProgressBarDelegate::paintButton2(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    static QStringList texts = { tr("cancel"), tr("download"), tr("browser") };
    QStyleOptionButton opt;
    QRect area(0, 0, 51*2, 28*2);
    area.moveCenter(option.rect.center());

    opt.rect = area;
    opt.state = option.state;
    QPalette palette = option.palette;
    palette.setColor(QPalette::Normal, QPalette::Window, QColor(Qt::blue));
    palette.setColor(QPalette::Normal, QPalette::Text, QColor(Qt::red));
    palette.setBrush(QPalette::Normal, QPalette::Button, QColor(Qt::blue));
    palette.setColor(QPalette::Normal, QPalette::ButtonText, QColor(Qt::red));
    opt.palette = palette;

    opt.features = QStyleOptionButton::None;
    opt.text = texts.at((index.row() % 3));

    painter->save();
    QFont textFont = painter->font();
    textFont.setPixelSize(12);
    painter->setFont(textFont);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
    painter->restore();
}
void ProgressBarDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if( index.column() == 0 && index.row()==0 )
    {
		//int percent = index.data().toInt();
		//QStyleOptionProgressBar progressBarOption;
		//progressBarOption.initFrom( &m_bar );
  //      QRect area(0, 0, 86, option.rect.height() - 2);
  //      area.moveCenter(option.rect.center());
		//progressBarOption.rect = area;
		//progressBarOption.minimum = 0;
		//progressBarOption.maximum = 100;
		//progressBarOption.progress = percent;
		////progressBarOption.text = QString::number( percent ) + "%";
  //      progressBarOption.text = tr("upload %1%").arg(QString::number(percent));
		//progressBarOption.textVisible = true;
		//progressBarOption.textAlignment = Qt::AlignCenter;

		//painter->save();
		//QStyle *drawStyle = m_bar.style();
		//drawStyle->drawControl( QStyle::CE_ProgressBar, &progressBarOption, painter, &m_bar );
		//painter->restore();
		//return;
        return paintProgressBar3(painter, option, index);
		
	}
    else if (index.column() == 0 && index.row() == 1)
    {
        return paintProgressBar1(painter, option, index);
    }
    else if (index.column() == 0 && index.row() == 2)
    {
        return paintProgressBar2(painter, option, index);
    }
	
    else if (index.column() == 0 && index.row() == 3)
    {
        //QAbstractItemView* x = qobject_cast<QAbstractItemView*>(parent());
        //QPushButton* btn = new QPushButton("QPushButton", x);
        //QPixmap map = QPixmap::grabWidget(btn);
        //painter->drawPixmap(option.rect.x(), option.rect.y(), map);
        //return;
    }
    else if (index.column() == 0 && index.row() == 4)
    {
        //QAbstractItemView* x = qobject_cast<QAbstractItemView*>(parent());
        //GameListItemView* btn = new GameListItemView(x);
        //QPixmap map = QPixmap::grabWidget(btn);
        //painter->drawPixmap(option.rect.x(), option.rect.y(), map);
        //return;
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
    else if (index.column() == 0 && index.row() == 7)
    {
        //QRect rect = option.rect;
        //if (option.state & QStyle::State_Selected)
        //{
        //    painter->fillRect(option.rect, option.palette.window());
        //}

        //QRect dst = rect;
        //dst.setLeft(rect.left() + GAME_LIST_PADDING * 2 + GAME_ICON_SIZE + GAME_LIST_TEXT_LEFT_PADDING);
        //dst.setTop(rect.top() + GAME_LIST_PADDING);
        //dst.setBottom(dst.top() + GAME_ICON_SIZE / 2);

        //QFont fontTitle = painter->font();
        //fontTitle.setBold(true);
        //fontTitle.setPointSize(14);

        //QPen titlePen = painter->pen();
        //titlePen.setColor(Qt::red);   // text color
        //                              // titlePen.setBrush(Qt::blue);


        //painter->save();
        //painter->setFont(fontTitle);
        //painter->setPen(titlePen);
        //painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, "Name");
        //painter->restore();

        //dst = rect;
        //dst.setLeft(rect.left() + GAME_LIST_PADDING * 2 + GAME_ICON_SIZE + GAME_LIST_TEXT_LEFT_PADDING);
        //dst.setTop(rect.top() + GAME_LIST_PADDING + GAME_ICON_SIZE / 2);
        //dst.setBottom(dst.top() + GAME_ICON_SIZE / 2);
        //painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, "123456987");

        //dst = rect;
        //dst.setRight(rect.left() + GAME_LIST_PADDING * 2 + GAME_ICON_SIZE);
        //QRect area(0, 0, GAME_ICON_SIZE, GAME_ICON_SIZE);
        //area.moveCenter(dst.center());
        //QPixmap pixmap("sgame.png");
        //painter->drawPixmap(area, pixmap);


        //return;
    }
    else if (index.column() == 0 && index.row() == 8)
    {
        //QStyleOptionButton opt;
        //opt.rect = option.rect;
        //opt.state = option.state;
        //opt.palette = option.palette;
        //opt.text = "QPushButton";
        //QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
        //return;
        paintButton1(painter, option, index);
    }
    else if (index.column() == 0 && index.row() == 9)
    {
        //QStyleOptionButton opt;
        //opt.rect = option.rect;
        //opt.state = option.state;
        //opt.palette = option.palette;
        //opt.text = "QPushButton";
        //QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
        //return;
        paintButton2(painter, option, index);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
	
	
}

QSize ProgressBarDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    if (index.column() == 0 && (index.row() == 0 || index.row() == 1 || index.row() == 2))
    {
        size.setHeight(36);
    }
	else if (index.column() == 0 && index.row() == 3)
	{
		size.setHeight(30);
	}
    else if (index.column() == 0 && index.row() == 4)
    {
        size.setHeight(80);
    }
    else if (index.column() == 0 && (index.row() == 7 || index.row() == 5 || index.row() == 6))
    {
        size.setHeight(GAME_ICON_SIZE + GAME_LIST_PADDING * 2);
    }
    else if (index.column() == 0 && index.row() == 8)
    {
        size.setHeight(60);
    }
    else if (index.column() == 0 && index.row() == 9)
    {
        size.setHeight(60);
    }
    return size;
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