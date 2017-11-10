#include "mv.h"
#include <QtWidgets/QApplication>
#include <QTableView>
#include "currencymodel.h"

#include <QSplitter>

#include <QHeaderView>
#include <QTreeView>
#include <QListView>
#include <QTableView>

#include <QStandardItemModel>
#include <QItemEditorFactory>
#include <QLineEdit>
#include <QSpinBox>
#include <QStandardItemEditorCreator>

void ChangeQItemEditorFactory();


int testQTableView(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QMap<QString, double> data;
	data["USD"] = 1.0000;
	data["CNY"] = 0.1628;
	data["GBP"] = 1.5361;
	data["EUR"] = 1.2992;
	data["HKD"] = 0.1289;

	QTableView view;
	CurrencyModel *model = new CurrencyModel(&view);
	model->setCurrencyMap(data);
	view.setModel(model);
	view.resize(600, 300);
	view.show();

	return a.exec();
}

int testQStandardItemModel(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QTreeView *tree = new QTreeView();
	QListView *list = new QListView();
	QTableView *table = new QTableView();

	QSplitter splitter;
	splitter.addWidget(tree);
	splitter.addWidget(list);
	splitter.addWidget(table);

	QStandardItemModel model(5, 2);  // row col
	for (int r = 0; r<5; r++)
		for (int c = 0; c<2; c++)
		{
			QStandardItem *item = new QStandardItem(QString("Row:%0, Column:%1").arg(r).arg(c));

			if (c == 0)
				for (int i = 0; i<3; i++)
				{
					QStandardItem *child = new QStandardItem(QString("Item %0").arg(i));
					child->setEditable(false);
					item->appendRow(child);
				}

			model.setItem(r, c, item);
		}

	model.setHorizontalHeaderItem(0, new QStandardItem("Foo"));
	model.setHorizontalHeaderItem(1, new QStandardItem("Bar-Baz"));

	tree->setModel(&model);
	list->setModel(&model);
	table->setModel(&model);

	list->setSelectionModel(tree->selectionModel());
	table->setSelectionModel(tree->selectionModel());

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	splitter.show();

	return app.exec();
}
#include "TableModelTest1.h"
#include "NameNumberInfo.h"

int testNameNumberInfo(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTableView table;

	// Basic and optional formatting for the table and its headers.
	// table.setShowGrid(false);

	// table.verticalHeader()->setVisible(false);
	// table.horizontalHeader()->setVisible(false);
	// table.horizontalHeader()->setStretchLastSection(true);

	std::vector<std::unique_ptr<DataRow>> numbers;
	numbers.push_back(std::unique_ptr<DataRow>(new NameNumberInfo("Row 1", 0, -1, 20)));
	numbers.push_back(std::unique_ptr<DataRow>(new NameNumberInfo("Row 2", 1, 1, 5)));

	TableModelTest1 model(numbers);
	table.setModel(&model);
	TableItemTest1Delegate delegate(&table);
	table.setItemDelegate(&delegate);

	ChangeQItemEditorFactory();

	table.show();

	return a.exec();
}

int testQListView(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QListView listView;

	QAbstractItemModel *model = new QStandardItemModel(4, 1, &listView);
	QIcon icon("sgame.png");
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Label"));
	model->setData(model->index(0, 0, QModelIndex()), "11");
	model->setData(model->index(1, 0, QModelIndex()), "11");
	model->setData(model->index(2, 0, QModelIndex()), "11");
	model->setData(model->index(2, 0, QModelIndex()), QColor(Qt::green), Qt::DecorationRole);
	model->setData(model->index(2, 0, QModelIndex()), QObject::tr("xxxx"), Qt::ToolTipRole);
	model->setData(model->index(3, 0, QModelIndex()), "11", Qt::DisplayRole);
	
	model->setData(model->index(3, 0, QModelIndex()), icon, Qt::DecorationRole);
	listView.setModel(model);

	listView.show();
	return a.exec();
}


int main(int argc, char *argv[])
{
	//return testQTableView(argc, argv);
	//return testQStandardItemModel(argc, argv);
	//return testNameNumberInfo(argc, argv);
	//return testQListView(argc, argv);

	QApplication a(argc, argv);

	MV w;
	w.show();

	return a.exec();
}

void ChangeQItemEditorFactory()
{
	QItemEditorFactory * factory = new QItemEditorFactory;

	QItemEditorCreatorBase * stringEditor = new QStandardItemEditorCreator<QLineEdit>();
	factory->registerEditor(QVariant::String, stringEditor);

	QItemEditorCreatorBase * intEditor = new QStandardItemEditorCreator<QSpinBox>();
	factory->registerEditor(QVariant::Int, intEditor);

	QItemEditorFactory::setDefaultFactory(factory);
}
