#include "Sample.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>

Sample::Sample(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	initUI();
}

void MainWindow::initUI()
{
	QVBoxLayout* vbox = new QVBoxLayout(this);
	QPushButton* btnOpenDir = new QPushButton("Open Dir", this);
	QPushButton* btnOpenFile = new QPushButton("Open File", this);
	label = new QLabel("MainWindow", this);
	

	//vbox->setSpacing(3);
	vbox->addWidget(btnOpenDir);
	vbox->addWidget(btnOpenFile);
	vbox->addWidget(label);
	

	setLayout(vbox);

	connect(btnOpenDir, &QPushButton::clicked, this, &MainWindow::openDirDialog);
	connect(btnOpenFile, &QPushButton::clicked, this, &MainWindow::openFileDialog);
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
	}
}
