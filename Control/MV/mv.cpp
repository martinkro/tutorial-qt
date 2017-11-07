#include "mv.h"
#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include <QStandardItemModel>
#include <QTableView>
#include <QProgressBar>
#include "spinboxdelegate.h"

MV::MV(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//testQStringListModel();
	//testQFileSystemModel();
	//testSpinBoxDelegate();
	//testQTableView();
	testQProgressBar();

	resize(900, 600);
}

void MV::testQProgressBar()
{
	QProgressBar* x = new QProgressBar(this);
	x->setFixedWidth(400);
	x->setMaximum(100);
	x->setMinimum(0);
	x->setTextVisible(true);
	x->setOrientation(Qt::Horizontal);
	x->setValue(100);
	x->setAlignment(Qt::AlignCenter);
	x->setFormat("check %p%");
}

void MV::testQTableView()
{
	// Create a new model
	// QStandardItemModel(int rows, int columns, QObject * parent = 0)
	auto model = new QStandardItemModel(4, 2, this);

	// Attach the model to the view
	QTableView* tableView = new QTableView(this);
	tableView->setModel(model);

	// Generate data
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 2; col++)
		{
			QModelIndex index
				= model->index(row, col, QModelIndex());
			// 0 for all data
			model->setData(index, 0);
		}
	}
}

void MV::testQStringListModel()
{
	QStringList data;
	data << "Letter A" << "Letter B" << "Letter C";
	auto model = new QStringListModel(this);
	model->setStringList(data);

	auto listView = new QListView(this);
	listView->setModel(model);

	QHBoxLayout *btnLayout = new QHBoxLayout;
	QPushButton *insertBtn = new QPushButton(tr("insert"), this);
	connect(insertBtn, &QPushButton::clicked, [=]() {
		bool isOK;
		QString text = QInputDialog::getText(this, "Insert",
			"Please input new data:",
			QLineEdit::Normal,
			"You are inserting new data.",
			&isOK);
		if (isOK) {
			QModelIndex currIndex = listView->currentIndex();
			model->insertRows(currIndex.row(), 1);
			model->setData(currIndex, text);
			listView->edit(currIndex);
		}

	});

	QPushButton *delBtn = new QPushButton(tr("Delete"), this);
	connect(delBtn, &QPushButton::clicked, [=]() {
		if (model->rowCount() > 1) {
			model->removeRows(listView->currentIndex().row(), 1);
		}
	});

	QPushButton *showBtn = new QPushButton(tr("Show"), this);
	connect(showBtn, &QPushButton::clicked, [=]() {

		QStringList data = model->stringList();
		QString str;
		foreach(QString s, data) {
			str += s + "\n";
		}
		QMessageBox::information(this, "Data", str);
	});

	btnLayout->addWidget(insertBtn);
	btnLayout->addWidget(delBtn);
	btnLayout->addWidget(showBtn);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(listView);
	mainLayout->addLayout(btnLayout);
	setLayout(mainLayout);
}

void MV::testQFileSystemModel()
{
	auto model = new QFileSystemModel;
	model->setRootPath(QDir::currentPath());

	auto treeView = new QTreeView(this);
	treeView->setModel(model);
	treeView->setRootIndex(model->index(QDir::currentPath()));

	QPushButton *mkdirButton = new QPushButton(tr("Make Directory..."), this);
	QPushButton *rmButton = new QPushButton(tr("Remove"), this);
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(mkdirButton);
	buttonLayout->addWidget(rmButton);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(treeView);
	layout->addLayout(buttonLayout);

	setLayout(layout);
	setWindowTitle("File System Model");

	connect(mkdirButton, &QPushButton::clicked, [=]() {
		QModelIndex index = treeView->currentIndex();
		if (!index.isValid()) {
			return;
		}
		QString dirName = QInputDialog::getText(this,
			tr("Create Directory"),
			tr("Directory name"));
		if (!dirName.isEmpty()) {
			if (!model->mkdir(index, dirName).isValid()) {
				QMessageBox::information(this,
					tr("Create Directory"),
					tr("Failed to create the directory"));
			}
		}
	});
	connect(rmButton, &QPushButton::clicked, [=]() {
	
		QModelIndex index = treeView->currentIndex();
		if (!index.isValid()) {
			return;
		}
		bool ok;
		if (model->fileInfo(index).isDir()) {
			ok = model->rmdir(index);
		}
		else {
			ok = model->remove(index);
		}
		if (!ok) {
			QMessageBox::information(this,
				tr("Remove"),
				tr("Failed to remove %1").arg(model->fileName(index)));
		}
	});
}

void MV::testSpinBoxDelegate()
{
	QStringList data;
	data << "0" << "1" << "2";
	auto model = new QStringListModel(this);
	model->setStringList(data);

	auto listView = new QListView(this);
	listView->setModel(model);
	listView->setItemDelegate(new SpinBoxDelegate(listView));

	QPushButton *btnShow = new QPushButton(tr("Show Model"), this);
	//connect(btnShow, SIGNAL(clicked()),
	//	this, SLOT(showModel()));
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(btnShow);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(listView);
	layout->addLayout(buttonLayout);
	setLayout(layout);
}
