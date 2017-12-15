#include "XTreeView.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QDir>
#include <QLabel>
#include <string>
#include <QMainWindow>
#include "XJsonModel.h"
#include "SimpleTreeModel.h"
#include "SimpleTreeModel2.h"
#include "SimpleTreeModel3.h"
#include "ZipFileTreeModel.h"
#include "ZipFileTreeModel2.h"
#include "ZipFileTreeModel3.h"
#include <QDirModel>
#include <QProgressBar>
#include <QPushButton>

// http://doc.qt.io/qt-5/qtwidgets-itemviews-fetchmore-example.html
// http://blog.sina.com.cn/s/blog_a6fb6cc90102v7q8.html
// https://group.cnblogs.com/topic/12027.html
// verticalScrollbarValueChanged

XTreeView::XTreeView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QTreeView* tree = new QTreeView;
	//QStandardItemModel* model = new QStandardItemModel(4, 2, tree);
	//tree->setModel(model);

	//QFileSystemModel* modelFile = new QFileSystemModel(tree);
	//modelFile->setRootPath(QDir::currentPath());;
	//tree->setModel(modelFile);
	//tree->setRootIndex(modelFile->index(QDir::currentPath()));

	//XJsonModel* model = new XJsonModel(tree);
	//tree->setModel(model);

	//std::string json = R"({
 //                      "firstName": "John",
 //                      "lastName": "Smith",
 //                      "age": 25,
 //                      "address":
 //                      {
 //                          "streetAddress": "21 2nd Street",
 //                          "city": "New York",
 //                          "state": "NY",
 //                          "postalCode": "10021"
 //                      },
 //                      "phoneNumber":
 //                      [
 //                          {
 //                            "type": "home",
 //                            "number": "212 555-1234"
 //                          },
 //                          {
 //                            "type": "fax",
 //                            "number": "646 555-4567"
 //                          }
 //                      ]
 //                  })";
	//model->loadJson(QByteArray::fromStdString(json));

	//QFile file(":/default.txt");
	//file.open(QIODevice::ReadOnly);
	//SimpleTreeModel3* model = new SimpleTreeModel3(file.readAll());
	//file.close();
	//tree->setModel(model);

	ZipFileTreeModel* model = new ZipFileTreeModel("f:/Game/cf.shell.apk", tree);
	
	QStringList verifyFileList;
	verifyFileList << "lib/armeabi/libtersafe.so";
	//model->setVerifyFileList(verifyFileList);
	tree->setModel(model);

	QLabel* labelU = new QLabel;
	char16_t a[] = { 'T',0x6210, '\0' };
	std::u16string o = a;
	QString text = QString::fromStdU16String(o);
	labelU->setText(text);

	QPushButton* btnStore = new QPushButton(tr("Store"));
	QPushButton* btnCancel = new QPushButton(tr("Cancel"));

	//connect(btnStore, &QPushButton::clicked, [=]() {
	//	btnStore->setEnabled(false);
	//	btnCancel->setEnabled(false);
	//	model->storeData();
	//	btnStore->setEnabled(true);
	//	btnCancel->setEnabled(true);
	//});
	//connect(btnCancel, &QPushButton::clicked, [=]() {
	//	btnStore->setEnabled(false);
	//	btnCancel->setEnabled(false);
	//	model->restoreData();
	//	btnStore->setEnabled(true);
	//	btnCancel->setEnabled(true);
	//});

	QHBoxLayout* layoutButton = new QHBoxLayout;
	layoutButton->addWidget(btnStore);
	layoutButton->addWidget(btnCancel);

	QProgressBar* progressbarTest1 = new QProgressBar;
	progressbarTest1->setMinimum(0);
	progressbarTest1->setMaximum(0);
	progressbarTest1->setValue(0);

	QVBoxLayout* main = new QVBoxLayout;
	main->addWidget(tree);
	main->addLayout(layoutButton);
	main->addWidget(labelU);
	main->addWidget(progressbarTest1);

	setLayout(main);
}
