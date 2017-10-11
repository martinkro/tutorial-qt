#pragma once

#include <QtWidgets/QDialog>
#include "ui_webdemo.h"
#include <QtWebEngineWidgets/QWebEngineView>

class WebDemo : public QDialog
{
	Q_OBJECT

public:
	WebDemo(QWidget *parent = Q_NULLPTR);

private:
	Ui::WebDemoClass ui;
	QWebEngineView* webview;
};
