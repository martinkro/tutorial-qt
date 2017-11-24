#include "LocalHTML.h"
#include <QtWebEngineWidgets>

LocalHTML::LocalHTML(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWebEngineView *view = new QWebEngineView(this);
	view->load(QUrl("qrc:/html/index.shtml"));
	//QUrl url = QUrl::fromLocalFile("html/index.shtml");
	//view->load(url);
	setCentralWidget(view);

	resize(960, 600);
}
