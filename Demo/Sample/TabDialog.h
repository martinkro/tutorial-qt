#pragma once

#include <QDialog>
#include <QDIalogButtonBox>
#include <QFileInfo>
#include <QTabWidget>
//#include "ui_TabDialog.h"

class GeneralPage :public QWidget
{
	Q_OBJECT
public:
	explicit GeneralPage(const QFileInfo& fileInfo, QWidget* parent = 0);
};

class PermissionsPage :public QWidget
{
	Q_OBJECT
public:
	explicit PermissionsPage(const QFileInfo& fileInfo, QWidget* parent = 0);
};

class ApplicationPage :public QWidget
{
	Q_OBJECT
public:
	explicit ApplicationPage(const QFileInfo& fileInfo, QWidget* parent = 0);
};

class TabDialog : public QDialog
{
	Q_OBJECT

public:
	TabDialog(const QString& filename,QWidget *parent = Q_NULLPTR);
	~TabDialog();

private:
	//Ui::TabDialog ui;
	QTabWidget* tabWidget;
	QDialogButtonBox* buttonBox;
};
