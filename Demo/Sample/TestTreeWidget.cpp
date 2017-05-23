#include "TestTreeWidget.h"
#include <QPushButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>

TestListWidget::TestListWidget(QWidget* parent)
	:QWidget(parent)
{
	QListWidget* listWidget = new QListWidget();
	QLabel* label = new QLabel();
	label->setFixedWidth(70);

	listWidget->addItem(new QListWidgetItem(tr("IE")));
	listWidget->addItem(new QListWidgetItem( tr("Netscape")));
	listWidget->addItem(new QListWidgetItem(tr("Opera")));
	listWidget->addItem(new QListWidgetItem( tr("Safari")));
	listWidget->addItem(new QListWidgetItem( tr("TheWorld")));
	listWidget->addItem(new QListWidgetItem( tr("Traveler")));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(label);
	layout->addWidget(listWidget);

	setLayout(layout);

	connect(listWidget, SIGNAL(currentTextChanged(QString)),
		label, SLOT(setText(QString)));
}

TestTreeWidget::TestTreeWidget(QWidget *parent)
	: QWidget(parent)
{
	QTreeWidget* treeWidget = new QTreeWidget(this);
	treeWidget->setColumnCount(1);

	QTreeWidgetItem *root = new QTreeWidgetItem(treeWidget,QStringList(QString("Root")));
	root->setCheckState(0, Qt::Checked);
	
	QTreeWidgetItem *leaf1 = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
	leaf1->setCheckState(0, Qt::Checked);

	QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
	leaf2->setCheckState(0, Qt::Checked);

	QList<QTreeWidgetItem *> rootList;
	rootList << root;
	treeWidget->insertTopLevelItems(0, rootList);
	treeWidget->setHeaderHidden(true);
	
}

TestTreeWidget::~TestTreeWidget()
{
}

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	initUI();
}

void MainWindow::initUI()
{
	QVBoxLayout* vbox = new QVBoxLayout(this);


	label = new QLabel(tr("中文Test:"), this);

	QHBoxLayout* hbox1 = new QHBoxLayout();
	QHBoxLayout* hbox2 = new QHBoxLayout();

	
	QLabel* labelInputDir = new QLabel(tr("输入目录:"));
	leditTargetDir = new QLineEdit();
	QPushButton* btnOpenDir = new QPushButton(tr("浏览目录"));
	hbox1->addWidget(labelInputDir);
	hbox1->addWidget(leditTargetDir);
	hbox1->addWidget(btnOpenDir);

	QLabel* labelConfigPath = new QLabel(tr("配置文件:"));
	leditConfigFilePath = new QLineEdit();
	QPushButton* btnOpenFile = new QPushButton(tr("加载配置"), this);
	hbox2->addWidget(labelConfigPath);
	hbox2->addWidget(leditConfigFilePath);
	hbox2->addWidget(btnOpenFile);



	//vbox->setSpacing(3);
	vbox->addLayout(hbox1);
	vbox->addLayout(hbox2);
	vbox->addWidget(label);


	setLayout(vbox);

	connect(btnOpenDir, &QPushButton::clicked, this, &MainWindow::openDirDialog);
	connect(btnOpenFile, &QPushButton::clicked, this, &MainWindow::openFileDialog);
	connect(leditTargetDir, &QLineEdit::textChanged, this, &MainWindow::onLineEditConfigPathTextChanged);
}

void MainWindow::openFileDialog()
{
	QString filename = QFileDialog::getOpenFileName(
		this,
		"Open File",
		".",
		"All Files(*.*)"
	);

	if (filename.isNull() || filename.isEmpty())
	{
		return;
	}
	else
	{
		label->setText(filename);
	}
}

void MainWindow::openDirDialog()
{
	QString dirname = QFileDialog::getExistingDirectory(
		this,
		tr("Open Directory"),
		"."
	);

	if (dirname.isNull() || dirname.isEmpty())
	{
		return;
	}
	else
	{
		label->setText(dirname);
		leditTargetDir->setText(dirname);
	}
}

void MainWindow::onLineEditConfigPathTextChanged()
{
	QString path = leditTargetDir->text();
	if (path.isNull() || path.isEmpty())
	{
		return;
	}

	QDir temp = QDir(path);
	temp.cdUp();
	QString configPath = QDir(temp).filePath("obfuscar.xml");
	leditConfigFilePath->setText(configPath);
}
