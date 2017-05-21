#include "Control.h"
#include "gotocelldialog.h"
#include "plusminus.h"
#include "simplemenu.h"
#include "anothermenu.h"
#include "checkablemenu.h"
#include "toolbar.h"
#include "Skeleton.h"
#include <QtWidgets/QApplication>

int TestGoToCellDialog(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GoToCellDialog dlg;
	dlg.show();
	return a.exec();
}

int TestPlusMinus(int argc, char* argv[])
{
	QApplication app(argc, argv);

	PlusMinus window;

	window.resize(300, 190);
	window.setWindowTitle("Plus minus");
	window.show();

	return app.exec();
}

int TestSimpleMenu(int argc, char* argv[])
{
	QApplication app(argc, argv);

	SimpleMenu window;

	window.resize(250, 150);
	window.setWindowTitle("Simple menu");
	window.show();

	return app.exec();
}

int TestAnotherMenu(int argc, char* argv[])
{
	QApplication app(argc, argv);

	AnotherMenu window;

	window.resize(350, 200);
	window.setWindowTitle("Another menu");
	window.show();

	return app.exec();
}

int TestCheckableMenu(int argc, char* argv[])
{
	QApplication app(argc, argv);

	CheckableMenu window;

	window.resize(250, 150);
	window.setWindowTitle("Checkable menu");
	window.show();

	return app.exec();
}

int TestToolbar(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ToolBar window;

	window.resize(300, 200);
	window.setWindowTitle("QToolBar");
	window.show();

	return app.exec();
}

int TestSkeleton(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Skeleton window;

	window.resize(350, 250);
	window.setWindowTitle("Application skeleton");
	window.show();

	return app.exec();
}

int main(int argc, char *argv[])
{
	// return TestGoToCellDialog(argc, argv);
	// return TestPlusMinus(argc, argv);
	// return TestSimpleMenu(argc, argv);
	// return TestAnotherMenu(argc, argv);
	// return TestCheckableMenu(argc, argv);
	// return TestToolbar(argc, argv);
	return TestSkeleton(argc, argv);
}
