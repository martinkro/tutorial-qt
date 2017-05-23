#include "Sample.h"
#include "Cursors.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QTextCodec>

#include "TestTreeWidget.h"

int Test_simple(int argc, char* argv[])
{
	QApplication a(argc, argv);

	//Sample w;
	//w.show();

	QWidget window;
	window.resize(250, 150);
	window.setWindowTitle("Sample");
	window.show();

	return a.exec();
}
int Test_tooltip(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QWidget window;

	window.resize(250, 150);
	window.move(300, 300);
	window.setWindowTitle("ToolTip");
	window.setToolTip("QWidget");
	window.show();

	return app.exec();
}

int Test_icon(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QWidget window;

	window.resize(250, 150);
	window.setWindowTitle("Icon");
	window.setWindowIcon(QIcon("web.png"));
	window.show();

	return app.exec();
}

int Test_Cursors(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Cursors window;

	window.resize(350, 150);
	window.setWindowTitle("Cursors");
	window.show();

	return app.exec();
}

class MyButton : public QWidget {

public:
	MyButton(QWidget *parent = 0);
};

MyButton::MyButton(QWidget *parent)
	: QWidget(parent) {

	QPushButton *quitBtn = new QPushButton("Quit", this);
	quitBtn->setGeometry(50, 40, 75, 30);

	connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}

void SetCodec()
{
	//QTextCodec *codec = QTextCodec::codecForName("GBK");//ַי¿צ1
	//QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
}

int TestMainWindow(int argc, char* argv[])
{
	
	QApplication app(argc, argv);
	SetCodec();

	MainWindow window;

	window.resize(700, 150);
	window.setWindowTitle("MainWindow");
	window.show();

	return app.exec();
}

int TestWidgetListWidget(int argc, char* argv[])
{

	QApplication app(argc, argv);
	SetCodec();

	TestListWidget window;

	window.resize(700, 150);
	window.setWindowTitle("ListWidget");
	window.show();

	return app.exec();
}

int TestWidgetTreeWidget(int argc, char* argv[])
{

	QApplication app(argc, argv);
	SetCodec();

	TestTreeWidget window;

	window.resize(700, 150);
	window.setWindowTitle("TreeWidget");
	window.show();

	return app.exec();
}

int main(int argc, char *argv[])
{
	// return Test_simple(argc, argv);
	// return Test_tooltip(argc, argv);
	// return Test_icon(argc, argv);
	// return Test_Cursors(argc, argv);
	QString message = "输入目录：";
	// return TestMainWindow(argc, argv);
	// return TestWidgetListWidget(argc, argv);
	return TestWidgetTreeWidget(argc, argv);
}
