#pragma once

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>

class TestListWidget :public QWidget
{
	Q_OBJECT

public:
	TestListWidget(QWidget *parent = 0);

private:
	
	
};

class TestTreeWidget : public QWidget
{
	Q_OBJECT

public:
	TestTreeWidget(QWidget *parent = 0);
	~TestTreeWidget();
};

class MainWindow :public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = Q_NULLPTR);

private:
	void initUI();

private:
	QLabel* label;
	QLineEdit* leditTargetDir;
	QLineEdit* leditConfigFilePath;
private slots:
	void openFileDialog();
	void openDirDialog();
	void onLineEditConfigPathTextChanged();
};
