#include "Sample.h"
#include "Cursors.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QTextCodec>

#include "TestTreeWidget.h"
#include "TabDialog.h"

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

int TestWidgetTabDialog(int argc, char* argv[])
{

	QApplication app(argc, argv);
	SetCodec();

	TabDialog window(QObject::tr("e:/share/myhl.apk"));

	window.resize(400, 300);
	// window.setWindowTitle("Tab Dialog");
	window.show();

	return app.exec();
}

class MyTabWidget :public QTabWidget
{
public:
	MyTabWidget(QWidget* parent = 0) :QTabWidget(parent)
	{
		setParent(parent);
	}

	//Overridden method from QTabWidget
	QTabBar* tabBar()
	{
		return QTabWidget::tabBar();
	}
};

int TestMyTabWidget(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QMainWindow *window = new QMainWindow();


	window->setWindowTitle(QString::fromUtf8("Set QTabBar Tab  Button"));
	window->resize(336, 227);

	QWidget *centralWidget = new QWidget(window);
	MyTabWidget *tabs = new MyTabWidget(centralWidget);

	tabs->setFixedSize(330, 220);

	tabs->addTab(new QWidget(), "TAB 1");
	tabs->addTab(new QWidget(), "TAB 2");
	tabs->addTab(new QWidget(), "TAB 3");



	QPushButton* button1 = new QPushButton();
	button1->setFixedWidth(20);
	button1->setIcon(*(new QIcon("information-icon.png")));

	QPushButton* button2 = new QPushButton();
	button2->setFixedWidth(20);
	button2->setIcon(*(new QIcon("information-icon.png")));

	QPushButton* button3 = new QPushButton();
	button3->setFixedWidth(20);
	button3->setIcon(*(new QIcon("information-icon.png")));



	tabs->tabBar()->setTabButton(0, QTabBar::LeftSide, ((QWidget*)(button1)));
	tabs->tabBar()->setTabButton(1, QTabBar::LeftSide, ((QWidget*)(button2)));
	tabs->tabBar()->setTabButton(2, QTabBar::LeftSide, ((QWidget*)(button3)));


	window->setCentralWidget(centralWidget);

	window->show();
	return app.exec();
}

int main(int argc, char *argv[])
{
	// return Test_simple(argc, argv);
	// return Test_tooltip(argc, argv);
	// return Test_icon(argc, argv);
	// return Test_Cursors(argc, argv);
	//QString message = "输入目录：";
	// return TestMainWindow(argc, argv);
	// return TestWidgetListWidget(argc, argv);
	//return TestWidgetTreeWidget(argc, argv);

	// return TestWidgetTabDialog(argc, argv);
	return TestMyTabWidget(argc, argv);
}
