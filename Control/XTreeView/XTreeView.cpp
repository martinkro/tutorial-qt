#include "XTreeView.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QDir>

// http://doc.qt.io/qt-5/qtwidgets-itemviews-fetchmore-example.html
// http://blog.sina.com.cn/s/blog_a6fb6cc90102v7q8.html
// https://group.cnblogs.com/topic/12027.html

XTreeView::XTreeView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QTreeView* tree = new QTreeView;
	//QStandardItemModel* model = new QStandardItemModel(4, 2, tree);
	//tree->setModel(model);

	QFileSystemModel* modelFile = new QFileSystemModel(tree);
	modelFile->setRootPath(QDir::currentPath());;
	tree->setModel(modelFile);
	tree->setRootIndex(modelFile->index(QDir::currentPath()));

	QVBoxLayout* main = new QVBoxLayout;
	main->addWidget(tree);

	setLayout(main);
}
