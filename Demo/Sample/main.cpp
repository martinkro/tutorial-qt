#include "Sample.h"
#include "Cursors.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QPushButton>

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

int main(int argc, char *argv[])
{
	// return Test_simple(argc, argv);
	// return Test_tooltip(argc, argv);
	// return Test_icon(argc, argv);
	return Test_Cursors(argc, argv);
}
