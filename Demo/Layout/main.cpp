#include "Layout.h"
#include "Absolute.h"
#include "VerticalBox.h"
#include "Buttons.h"
#include "TestEvents.h"

#include <QtWidgets/QApplication>

int TestLayout(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Layout w;
	w.show();
	return a.exec();
}

int TestAbsolute(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Absolute window;

	window.setWindowTitle("Absolute");
	window.show();

	return app.exec();
}

int TestVerticalBox(int argc, char* argv[])
{
	QApplication app(argc, argv);

	VerticalBox window;

	window.resize(240, 230);
	window.setWindowTitle("VerticalBox");
	window.show();

	return app.exec();
}

int TestButtons(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Buttons window;

	window.resize(290, 170);
	window.setWindowTitle("Buttons");
	window.show();

	return app.exec();
}

int TestLayouts(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Layouts window;

	window.setWindowTitle("Layouts");
	window.show();

	return app.exec();
}

int TestFormEx(int argc, char* argv[])
{
	QApplication app(argc, argv);

	FormEx window;

	window.setWindowTitle("Form example");
	window.show();

	return app.exec();
}

int TestGridLayout(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Calculator window;

	window.move(300, 300);
	window.setWindowTitle("Calculator");
	window.show();

	return app.exec();
}

int TestGridLayout2(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Review window;

	window.setWindowTitle("Review");
	window.show();

	return app.exec();
}

// Test events
int TestEventsClick(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Click window;

	window.resize(250, 150);
	window.setWindowTitle("Click");
	window.show();

	return app.exec();
}

int TestEventsKeyPress(int argc, char* argv[])
{
	QApplication app(argc, argv);

	KeyPress window;

	window.resize(250, 150);
	window.setWindowTitle("Key press");
	window.show();

	return app.exec();
}

int TestEventsMove(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Move window;

	window.resize(250, 150);
	window.setWindowTitle("Move");
	window.show();

	return app.exec();
}

int TestSignalDisconnect(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Disconnect window;

	window.resize(250, 150);
	window.setWindowTitle("Disconnect");
	window.show();

	return app.exec();
}

int TestTimer(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Timer window;

	window.resize(250, 150);
	window.setWindowTitle("Timer");
	window.show();

	return app.exec();
}

#include "TestWidgets.h"

int TestWidgetsLabel(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Label window;

	window.setWindowTitle("QLabel");
	window.show();

	return app.exec();
}

int TestWidgetsSlider(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Slider window;

	window.setWindowTitle("QSlider");
	window.show();

	return app.exec();
}

int TestWidgetsComboBox(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ComboBoxEx window;

	window.resize(300, 150);
	window.setWindowTitle("QComboBox");
	window.show();

	return app.exec();
}

int TestWidgetsSpinBox(int argc, char* argv[])
{
	QApplication app(argc, argv);

	SpinBox window;

	window.resize(250, 150);
	window.setWindowTitle("QSpinBox");
	window.show();

	return app.exec();
}

int TestWidgetsLineEdit(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Ledit window;

	window.setWindowTitle("QLineEdit");
	window.show();

	return app.exec();
}

int TestWidgetsStatusBar(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Statusbar window;

	window.resize(300, 200);
	window.setWindowTitle("QStatusBar");
	window.show();

	return app.exec();
}

int TestWidgetsCheckBox(int argc, char* argv[])
{
	QApplication app(argc, argv);

	CheckBox window;

	window.resize(250, 150);
	window.setWindowTitle("QCheckBox");
	window.show();

	return app.exec();
}

int TestWidgetsListView(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ListWidget window;

	window.setWindowTitle("QListWidget");
	window.show();

	return app.exec();
}

int TestWidgetsProgressBar(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ProgressBarEx window;

	window.resize(250, 150);
	window.setWindowTitle("QProgressBar");
	window.show();

	return app.exec();
}

int TestWidgetsPixMap(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Pixmap window;

	window.setWindowTitle("QPixmap");
	window.show();

	return app.exec();
}

int TestWidgetsSplitter(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Splitter window;

	window.resize(350, 300);
	window.setWindowTitle("QSplitter");
	window.show();

	return app.exec();
}

int TestWidgetsTableWidget(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Table window;

	window.resize(400, 250);
	window.setWindowTitle("QTableWidget");
	window.show();

	return app.exec();
}

int TestWidgetsCustomBurning(int argc, char* argv[])
{
	QApplication app(argc, argv);
	Burning window;

	window.resize(370, 200);
	window.setWindowTitle("The Burning widget");
	window.show();

	return app.exec();
}

#include "TestPainting.h"
int TestPaintingLines(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Lines window;

	window.resize(280, 270);
	window.setWindowTitle("Lines");
	window.show();

	return app.exec();
}

int TestPaintingColours(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Colours window;

	window.resize(360, 280);
	window.setWindowTitle("Colours");
	window.show();

	return app.exec();
}

int TestPaintingPatterns(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Patterns window;

	window.resize(350, 280);
	window.setWindowTitle("Patterns");
	window.show();

	return app.exec();
}

int TestPaintingTransparentRectangles(int argc, char* argv[])
{
	QApplication app(argc, argv);

	TransparentRectangles window;

	window.resize(630, 90);
	window.setWindowTitle("Transparent rectangles");
	window.show();

	return app.exec();
}

int TestPaintingDonut(int argc, char*argv[])
{
	QApplication app(argc, argv);

	Donut window;

	window.resize(350, 280);
	window.setWindowTitle("Donut");
	window.show();

	return app.exec();
}

int TestPaintingShapes(int argc, char*argv[])
{
	QApplication app(argc, argv);

	Shapes window;

	window.resize(350, 280);
	window.setWindowTitle("Shapes");
	window.show();

	return app.exec();
}

int TestPaintingLinearGradients(int argc, char* argv[])
{
	QApplication app(argc, argv);

	LinearGradients window;

	window.resize(350, 260);
	window.setWindowTitle("Linear gradients");
	window.show();

	return app.exec();
}

int TestPaintingRadialGradient(int argc, char*argv[])
{
	QApplication app(argc, argv);

	RadialGradient window;

	window.resize(300, 250);
	window.setWindowTitle("Radial gradient");
	window.show();

	return app.exec();
}

int TestPaintingPuff(int argc, char*argv[])
{
	QApplication app(argc, argv);

	Puff window;

	window.resize(350, 280);
	window.setWindowTitle("Puff");
	window.show();

	return app.exec();
}

#include "Snake.h"
int TestGameSnake(int argc, char*argv[])
{
	QApplication app(argc, argv);

	Snake window;

	window.setWindowTitle("Snake");
	window.show();

	return app.exec();
}

#include "Breakout.h"
int TestGameBreakout(int argc, char*argv[])
{
	QApplication app(argc, argv);

	Breakout window;

	window.resize(300, 400);
	window.setWindowTitle("Breakout");
	window.show();

	return app.exec();
}

int main(int argc, char *argv[])
{
	// return TestLayout(argc, argv);
	// return TestAbsolute(argc, argv);
	// return TestVerticalBox(argc, argv);
	// return TestButtons(argc, argv);
	// return TestLayouts(argc, argv);
	// return TestFormEx(argc, argv);
	// return TestGridLayout(argc, argv);
	// return TestGridLayout2(argc, argv);
	// return TestEventsClick(argc, argv);
	// return TestEventsKeyPress(argc, argv);
	// return TestEventsMove(argc, argv);
	// return TestSignalDisconnect(argc, argv);
	// return TestTimer(argc, argv);
	// return TestWidgetsLabel(argc, argv);
	// return TestWidgetsSlider(argc, argv);
	// return TestWidgetsComboBox(argc, argv);
	// return TestWidgetsSpinBox(argc, argv);
	// return TestWidgetsLineEdit(argc, argv);
	// return TestWidgetsStatusBar(argc, argv);
	// return TestWidgetsCheckBox(argc, argv);
	// return TestWidgetsListView(argc, argv);
	// return TestWidgetsProgressBar(argc, argv);
	// return TestWidgetsSplitter(argc, argv);
	// return TestWidgetsTableWidget(argc, argv);

	// return TestPaintingLines(argc, argv);
	// return TestPaintingColours(argc, argv);
	// return TestPaintingPatterns(argc, argv);
	// return TestPaintingTransparentRectangles(argc, argv);
	// return TestPaintingDonut(argc, argv);
	// return TestPaintingShapes(argc, argv);
	// return TestPaintingLinearGradients(argc, argv);
	// return TestPaintingRadialGradient(argc, argv);
	// return TestPaintingPuff(argc, argv);

	// return TestWidgetsCustomBurning(argc, argv);
	// return TestGameSnake(argc, argv);
	return TestGameBreakout(argc, argv);
}
