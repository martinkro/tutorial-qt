#include "webdemo.h"

WebDemo::WebDemo(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	webview = new QWebEngineView(this);
	webview->setUrl(QUrl(QStringLiteral("qrc:/login.html")));
}
