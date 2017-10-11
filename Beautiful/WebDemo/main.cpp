#include "webdemo.h"
#include <QtWidgets/QApplication>
#include <QtWebEngineWidgets/QWebEngineView>

#include "browser.h"
#include "browserwindow.h"
#include "webview.h"
#include <QApplication>
#include <QWebEngineSettings>

QUrl getCommandLineUrlArgument()
{
	const QStringList args = QCoreApplication::arguments();
	if (args.count() > 1)
		return QUrl::fromUserInput(args.last());
	return QUrl();
}

int browser(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));

	QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

	QUrl url = getCommandLineUrlArgument();
	if (!url.isValid())
		url = QStringLiteral("qrc:/login1.html");

	Browser browser;
	BrowserWindow *window = browser.createWindow();
	window->currentTab()->setUrl(url);

	return app.exec();
}

int qqlogin(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);

	QWebEngineView view;
	view.setUrl(QUrl(QStringLiteral("qrc:/login1.html")));
	view.resize(400, 300);
	view.show();

	return app.exec();
}

int main(int argc, char *argv[])
{
	return browser(argc, argv);
	//return qqlogin(argc, argv);
}
