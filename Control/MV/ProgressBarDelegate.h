#ifndef PROGRESSBARDELETEGATE_HPP
#define PROGRESSBARDELETEGATE_HPP

#include <QStyledItemDelegate>
#include <QTreeWidget>
#include <QProgressBar>

class ProgressBarDelegate : public QStyledItemDelegate
{
	Q_OBJECT
	public:
		ProgressBarDelegate( int column, QWidget* p = nullptr );
		~ProgressBarDelegate();
		void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		QSize sizeHint(const QStyleOptionViewItem &option,
			const QModelIndex &index) const;

		static bool setItem( QTreeWidgetItem* item, int column, int progress );
		static void initItem( QTreeWidgetItem* item, int column, int total );
	protected:
		int m_column;
		QProgressBar m_bar;
};

class Progress
{
	public:
		Progress() : progress(0), total(0) {}
		Progress(int p, int t ) : progress(p), total(t) {}
		int percent() const
		{
			return static_cast< int >(
					( static_cast<float>( progress ) / static_cast<float>( total ) ) * 100 );
		}
		bool isFinished() const
		{
			return progress == total;
		}
		int progress;
		int total;
};

// 在使用Qt进行应用程序开发时，经常要自定义数据类型，而且在需要的时候还要把这些数据放到QVariant中去。
// 因为QVariant是一个接受绝大部分类型的数据类型。为了达到这个目的，就必须使用Q_DECLARE_METATYPE
// 该类型必须有公有的 构造、析构、复制构造 函数
Q_DECLARE_METATYPE( Progress );

#endif