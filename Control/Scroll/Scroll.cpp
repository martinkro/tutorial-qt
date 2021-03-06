#include "Scroll.h"
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QTableView>
#include <QStandardItemModel>
#include <QScrollBar>
#include <ctime>
#include <QDateTime>

void verticalResizeTableViewToContents(QTableView *tableView)
{
	int count = tableView->verticalHeader()->count();
	int scrollBarHeight = tableView->horizontalScrollBar()->height();
	int horizontalHeaderHeight = tableView->horizontalHeader()->height();
	int rowTotalHeight = 0;
	for (int i = 0; i < count; ++i) {
		rowTotalHeight += tableView->verticalHeader()->sectionSize(i);
	}
	tableView->setMinimumHeight(horizontalHeaderHeight + rowTotalHeight + scrollBarHeight);
}

void verticalResizeTreeViewToContents(QTreeView *tableView)
{
	//int count = tableView->header()->count();
	QModelIndex indexRoot = tableView->rootIndex();
	//index.model();
	int count = tableView->model()->rowCount(indexRoot);
	
	int scrollBarHeight = tableView->horizontalScrollBar()->height();
	int horizontalHeaderHeight = tableView->header()->height();
	int rowTotalHeight = 0;
	for (int i = 0; i < count; ++i) {
		//rowTotalHeight += tableView->verticalHeader()->sectionSize(i);
		QRect rect = tableView->visualRect(tableView->model()->index(i,0,indexRoot));
		rowTotalHeight += rect.height();
	}
	tableView->setMinimumHeight(horizontalHeaderHeight + rowTotalHeight + scrollBarHeight + 14*2);
}

Scroll::Scroll(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QWidget* w = new QWidget;
	//w->setBackgroundRole(QPalette::Base);
	w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	QVBoxLayout* v = new QVBoxLayout;

	int i = 0;
	for (i = 0; i < 2; i++)
	{
		QLabel* label = new QLabel(tr("Label %1").arg(i));
		v->addWidget(label);
	}

	QTableView* table = new QTableView;
	
	//table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QStandardItemModel* modelTable = new QStandardItemModel(6, 2, table);
	
	modelTable->setData(modelTable->index(0,0), "libunity.so", Qt::DisplayRole);
	modelTable->setData(modelTable->index(0, 0), Qt::Checked, Qt::CheckStateRole);
	table->setModel(modelTable);
	table->verticalHeader()->setVisible(false);
	table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	// 实时计算高度
	verticalResizeTableViewToContents(table);
	v->addWidget(table);

	for (; i < 3; i++)
	{
		QLabel* label = new QLabel(tr("Label %1").arg(i));
		v->addWidget(label);
	}

	QTreeView* tree = new QTreeView;
	QStandardItemModel* modelTree = new QStandardItemModel(10, 2, tree);
	tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	tree->setModel(modelTree);
	verticalResizeTreeViewToContents(tree);
	v->addWidget(tree);

	w->setLayout(v);


	QScrollArea* scroll = new QScrollArea(this);
	scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scroll->setWidgetResizable(true);
	//scroll->setScaledContents(true);
	scroll->setWidget(w);
	//QTableView* tx = new QTableView;
	//QStandardItemModel* model = new QStandardItemModel(14, 2, tx);
	//tx->setModel(model);
	//scroll->setWidget(tx);

	
	
	QPushButton* btn = new QPushButton(tr("QPushButton"));
	QPushButton* btn2 = new QPushButton(tr("QPushButton"));
	QHBoxLayout* layoutButton = new QHBoxLayout;
	layoutButton->addWidget(btn);
	layoutButton->addWidget(btn2);

	
	QLabel* labelSignatureYes = new QLabel(tr("<p><img align='center' src=\"ok_24px.png\" /><font size='24px'>Signature Config:YES</font></p>"));
	labelSignatureYes->setTextFormat(Qt::RichText);
	// labelSignatureYes->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);

	QLabel* labelTest = new QLabel;
	labelTest->setObjectName("test");
	labelTest->setText(tr("Test QLabel"));
	//labelTest->setPixmap(QPixmap("ok_24px.png"));

	QWidget* wLabel = new QWidget;
	QLabel* icon = new QLabel;
	icon->setPixmap(QPixmap("ok_24px.png"));
	QLabel* text = new QLabel(tr("Signature Config:YES"));
	QHBoxLayout* layoutLabel = new QHBoxLayout;

	QLabel* labelTime = new QLabel;

	QPushButton* btnConfig = new QPushButton(tr("Go to config"));
	btnConfig->setObjectName("config");
	layoutLabel->addWidget(icon);
	layoutLabel->addWidget(text);
	layoutLabel->addWidget(btnConfig);
	layoutLabel->addWidget(labelTime);
	layoutLabel->addStretch();
	wLabel->setLayout(layoutLabel);

	std::time_t x = std::time(nullptr);
	QDateTime date = QDateTime::fromTime_t(x);
	QString strTime = date.toString("MM-dd hh:mm");
	labelTime->setText(strTime);

	QVBoxLayout* main = new QVBoxLayout;
	main->addWidget(scroll);
	main->addLayout(layoutButton);
	main->addWidget(labelSignatureYes);
	main->addWidget(labelTest);
	main->addWidget(wLabel);
	setLayout(main);
	//scroll->setWidget(this);
	
}
