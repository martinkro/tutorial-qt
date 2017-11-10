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

// ��ʹ��Qt����Ӧ�ó��򿪷�ʱ������Ҫ�Զ����������ͣ���������Ҫ��ʱ��Ҫ����Щ���ݷŵ�QVariant��ȥ��
// ��ΪQVariant��һ�����ܾ��󲿷����͵��������͡�Ϊ�˴ﵽ���Ŀ�ģ��ͱ���ʹ��Q_DECLARE_METATYPE
// �����ͱ����й��е� ���졢���������ƹ��� ����
Q_DECLARE_METATYPE( Progress );

#endif