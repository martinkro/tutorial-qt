#pragma once

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QSpinBox>
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QProgressBar>
#include <QWidget>
#include <QSlider>
#include <QFrame>

class TestWidgets : public QWidget
{
	Q_OBJECT

public:
	TestWidgets(QWidget *parent);
	~TestWidgets();
};

class Label : public QWidget {

public:
	Label(QWidget *parent = 0);

private:
	QLabel *label;
};

class Slider : public QWidget {

	Q_OBJECT

public:
	Slider(QWidget *parent = 0);

private:
	QSlider *slider;
	QLabel *label;
};

class ComboBoxEx : public QWidget {

	Q_OBJECT

public:
	ComboBoxEx(QWidget *parent = 0);

private:
	QComboBox *combo;
	QLabel *label;
};

class SpinBox : public QWidget {

	Q_OBJECT

public:
	SpinBox(QWidget *parent = 0);

private:
	QSpinBox *spinbox;
};

class Ledit : public QWidget {

public:
	Ledit(QWidget *parent = 0);
};

class Statusbar : public QMainWindow {

	Q_OBJECT

public:
	Statusbar(QWidget *parent = 0);

	private slots:
	void OnOkPressed();
	void OnApplyPressed();

private:
	QPushButton *okBtn;
	QPushButton *aplBtn;
};

class CheckBox : public QWidget {

	Q_OBJECT

public:
	CheckBox(QWidget *parent = 0);

	private slots:
	void showTitle(int);
};

class ListWidget : public QWidget {

	Q_OBJECT

public:
	ListWidget(QWidget *parent = 0);

	private slots:
	void addItem();
	void renameItem();
	void removeItem();
	void clearItems();

private:
	QListWidget *lw;
	QPushButton *add;
	QPushButton *rename;
	QPushButton *remove;
	QPushButton *removeAll;
};

class ProgressBarEx : public QWidget {

	Q_OBJECT

public:
	ProgressBarEx(QWidget *parent = 0);

private:
	int progress;
	QTimer *timer;
	QProgressBar *pbar;
	QPushButton *startBtn;
	QPushButton *stopBtn;
	static const int DELAY = 200;
	static const int MAX_VALUE = 100;

	void updateBar();
	void startMyTimer();
	void stopMyTimer();
};

class Pixmap : public QWidget {

public:
	Pixmap(QWidget *parent = 0);
};

class Splitter : public QWidget {

public:
	Splitter(QWidget *parent = 0);
};


class Table : public QWidget {

public:
	Table(QWidget *parent = 0);
};

class Burning;
class Widget : public QFrame {

public:
	Widget(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *e);
	void drawWidget(QPainter &qp);

private:
	QWidget *m_parent;
	Burning *burn;

	static const int DISTANCE = 19;
	static const int LINE_WIDTH = 5;
	static const int DIVISIONS = 10;
	static const float FULL_CAPACITY; //= 700.0f;
	static const float MAX_CAPACITY;// = 750.0f;
};

class Burning : public QFrame {

	Q_OBJECT

public:
	Burning(QWidget *parent = 0);
	int getCurrentWidth();

	public slots:
	void valueChanged(int);

private:
	QSlider *slider;
	Widget *widget;
	int cur_width;

	void initUI();
};


