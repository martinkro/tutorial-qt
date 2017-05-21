#include "TestWidgets.h"
#include <QVBoxLayout>
#include <QHboxLayout>
#include <QFont>
#include <QLineEdit>
#include <QFrame>
#include <QStatusBar>
#include <QCheckBox>
#include <QInputDialog>
#include <QTimer>
#include <QFrame>
#include <QSplitter>
#include <QTableWidget>
#include <QtGui>
#include <QPainter>

TestWidgets::TestWidgets(QWidget *parent)
	: QWidget(parent)
{
}

TestWidgets::~TestWidgets()
{
}

Label::Label(QWidget *parent)
	: QWidget(parent) {

	QString lyrics = "Who doesn't long for someone to hold\n\
Who knows how to love you without being told\n\
Somebody tell me why I'm on my own\n\
If there's a soulmate for everyone\n\
\n\
Here we are again, circles never end\n\
How do I find the perfect fit\n\
There's enough for everyone\n\
But I'm still waiting in line\n\
\n\
Who doesn't long for someone to hold\n\
Who knows how to love you without being told\n\
Somebody tell me why I'm on my own\n\
If there's a soulmate for everyone";

	label = new QLabel(lyrics, this);
	label->setFont(QFont("Purisa", 10));

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(label);
	setLayout(vbox);
}

Slider::Slider(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);

	slider = new QSlider(Qt::Horizontal, this);
	hbox->addWidget(slider);

	label = new QLabel("0", this);
	hbox->addWidget(label);

	connect(slider, &QSlider::valueChanged, label,
		static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
}

ComboBoxEx::ComboBoxEx(QWidget *parent)
	: QWidget(parent) {

	QStringList distros = { "Arch", "Xubuntu", "Redhat", "Debian",
		"Mandriva" };

	QHBoxLayout *hbox = new QHBoxLayout(this);

	combo = new QComboBox();
	combo->addItems(distros);

	hbox->addWidget(combo);
	hbox->addSpacing(15);

	label = new QLabel("Arch", this);
	hbox->addWidget(label);

	connect(combo, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
		label, &QLabel::setText);
}

SpinBox::SpinBox(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);
	hbox->setSpacing(15);

	spinbox = new QSpinBox(this);
	QLabel *lbl = new QLabel("0", this);

	hbox->addWidget(spinbox);
	hbox->addWidget(lbl);

	connect(spinbox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		lbl, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
}

Ledit::Ledit(QWidget *parent)
	: QWidget(parent) {

	QLabel *name = new QLabel("Name:", this);
	name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	QLabel *age = new QLabel("Age:", this);
	age->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	QLabel *occupation = new QLabel("Occupation:", this);
	occupation->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QLineEdit *le1 = new QLineEdit(this);
	QLineEdit *le2 = new QLineEdit(this);
	QLineEdit *le3 = new QLineEdit(this);

	QGridLayout *grid = new QGridLayout();

	grid->addWidget(name, 0, 0);
	grid->addWidget(le1, 0, 1);
	grid->addWidget(age, 1, 0);
	grid->addWidget(le2, 1, 1);
	grid->addWidget(occupation, 2, 0);
	grid->addWidget(le3, 2, 1);

	setLayout(grid);
}

Statusbar::Statusbar(QWidget *parent)
	: QMainWindow(parent) {

	QFrame *frame = new QFrame(this);
	setCentralWidget(frame);

	QHBoxLayout *hbox = new QHBoxLayout(frame);

	okBtn = new QPushButton("OK", frame);
	hbox->addWidget(okBtn, 0, Qt::AlignLeft | Qt::AlignTop);

	aplBtn = new QPushButton("Apply", frame);
	hbox->addWidget(aplBtn, 1, Qt::AlignLeft | Qt::AlignTop);

	statusBar();

	connect(okBtn, &QPushButton::clicked, this, &Statusbar::OnOkPressed);
	connect(aplBtn, &QPushButton::clicked, this, &Statusbar::OnApplyPressed);
}

void Statusbar::OnOkPressed() {

	statusBar()->showMessage("OK button pressed", 2000);
}

void Statusbar::OnApplyPressed() {

	statusBar()->showMessage("Apply button pressed", 2000);
}

CheckBox::CheckBox(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);

	QCheckBox *cb = new QCheckBox("Show Title", this);
	cb->setCheckState(Qt::Checked);
	hbox->addWidget(cb, 0, Qt::AlignLeft | Qt::AlignTop);

	connect(cb, &QCheckBox::stateChanged, this, &CheckBox::showTitle);
}

void CheckBox::showTitle(int state) {

	if (state == Qt::Checked) {
		setWindowTitle("QCheckBox");
	}
	else {
		setWindowTitle(" ");
	}
}

ListWidget::ListWidget(QWidget *parent)
	: QWidget(parent) {

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setSpacing(10);

	QHBoxLayout *hbox = new QHBoxLayout(this);

	lw = new QListWidget(this);
	lw->addItem("The Omen");
	lw->addItem("The Exorcist");
	lw->addItem("Notes on a scandal");
	lw->addItem("Fargo");
	lw->addItem("Capote");

	add = new QPushButton("Add", this);
	rename = new QPushButton("Rename", this);
	remove = new QPushButton("Remove", this);
	removeAll = new QPushButton("Remove All", this);

	vbox->setSpacing(3);
	vbox->addStretch(1);
	vbox->addWidget(add);
	vbox->addWidget(rename);
	vbox->addWidget(remove);
	vbox->addWidget(removeAll);
	vbox->addStretch(1);

	hbox->addWidget(lw);
	hbox->addSpacing(15);
	hbox->addLayout(vbox);

	connect(add, &QPushButton::clicked, this, &ListWidget::addItem);
	connect(rename, &QPushButton::clicked, this, &ListWidget::renameItem);
	connect(remove, &QPushButton::clicked, this, &ListWidget::removeItem);
	connect(removeAll, &QPushButton::clicked, this, &ListWidget::clearItems);

	setLayout(hbox);
}

void ListWidget::addItem() {

	QString c_text = QInputDialog::getText(this, "Item", "Enter new item");
	QString s_text = c_text.simplified();

	if (!s_text.isEmpty()) {

		lw->addItem(s_text);
		int r = lw->count() - 1;
		lw->setCurrentRow(r);
	}
}

void ListWidget::renameItem() {

	QListWidgetItem *curitem = lw->currentItem();

	int r = lw->row(curitem);
	QString c_text = curitem->text();
	QString r_text = QInputDialog::getText(this, "Item",
		"Enter new item", QLineEdit::Normal, c_text);

	QString s_text = r_text.simplified();

	if (!s_text.isEmpty()) {

		QListWidgetItem *item = lw->takeItem(r);
		delete item;
		lw->insertItem(r, s_text);
		lw->setCurrentRow(r);
	}
}

void ListWidget::removeItem() {

	int r = lw->currentRow();

	if (r != -1) {

		QListWidgetItem *item = lw->takeItem(r);
		delete item;
	}
}

void ListWidget::clearItems() {

	if (lw->count() != 0) {
		lw->clear();
	}
}

ProgressBarEx::ProgressBarEx(QWidget *parent)
	: QWidget(parent) {

	progress = 0;
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &ProgressBarEx::updateBar);

	QGridLayout *grid = new QGridLayout(this);
	grid->setColumnStretch(2, 1);

	pbar = new QProgressBar();
	grid->addWidget(pbar, 0, 0, 1, 3);

	startBtn = new QPushButton("Start", this);
	connect(startBtn, &QPushButton::clicked, this, &ProgressBarEx::startMyTimer);
	grid->addWidget(startBtn, 1, 0, 1, 1);

	stopBtn = new QPushButton("Stop", this);
	connect(stopBtn, &QPushButton::clicked, this, &ProgressBarEx::stopMyTimer);
	grid->addWidget(stopBtn, 1, 1);
}

void ProgressBarEx::startMyTimer() {

	if (progress >= MAX_VALUE) {

		progress = 0;
		pbar->setValue(0);
	}

	if (!timer->isActive()) {

		startBtn->setEnabled(false);
		stopBtn->setEnabled(true);
		timer->start(DELAY);
	}
}

void ProgressBarEx::stopMyTimer() {

	if (timer->isActive()) {

		startBtn->setEnabled(true);
		stopBtn->setEnabled(false);
		timer->stop();
	}
}

void ProgressBarEx::updateBar() {

	progress++;

	if (progress <= MAX_VALUE) {

		pbar->setValue(progress);
	}
	else {

		timer->stop();
		startBtn->setEnabled(true);
		stopBtn->setEnabled(false);
	}
}

Pixmap::Pixmap(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);

	QPixmap pixmap("bojnice.jpg");

	QLabel *label = new QLabel(this);
	label->setPixmap(pixmap);

	hbox->addWidget(label, 0, Qt::AlignTop);
}

Splitter::Splitter(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);

	QFrame *topleft = new QFrame(this);
	topleft->setFrameShape(QFrame::StyledPanel);

	QFrame *topright = new QFrame(this);
	topright->setFrameShape(QFrame::StyledPanel);

	QSplitter *splitter1 = new QSplitter(Qt::Horizontal, this);
	splitter1->addWidget(topleft);
	splitter1->addWidget(topright);

	QFrame *bottom = new QFrame(this);
	bottom->setFrameShape(QFrame::StyledPanel);

	QSplitter *splitter2 = new QSplitter(Qt::Vertical, this);
	splitter2->addWidget(splitter1);
	splitter2->addWidget(bottom);

	QList<int> sizes({ 50, 100 });
	splitter2->setSizes(sizes);

	hbox->addWidget(splitter2);
}

Table::Table(QWidget *parent)
	: QWidget(parent) {

	QHBoxLayout *hbox = new QHBoxLayout(this);

	QTableWidget *table = new QTableWidget(25, 25, this);

	hbox->addWidget(table);
}

const int PANEL_HEIGHT = 30;
const float Widget::FULL_CAPACITY = 700.0f;
const float Widget::MAX_CAPACITY = 750.0f;

Widget::Widget(QWidget *parent)
	: QFrame(parent) {

	m_parent = parent;
	setMinimumHeight(PANEL_HEIGHT);
}

void Widget::paintEvent(QPaintEvent *e) {

	QPainter qp(this);
	drawWidget(qp);

	QFrame::paintEvent(e);
}

void Widget::drawWidget(QPainter &qp) {

	QString num[] = { "75", "150", "225", "300", "375", "450",
		"525", "600", "675" };

	int asize = sizeof(num) / sizeof(num[1]);

	QColor redColor(255, 175, 175);
	QColor yellowColor(255, 255, 184);

	int width = size().width();

	Burning *burn = (Burning *)m_parent;
	int cur_width = burn->getCurrentWidth();

	int step = (int)qRound((double)width / DIVISIONS);
	int till = (int)((width / MAX_CAPACITY) * cur_width);
	int full = (int)((width / MAX_CAPACITY) * FULL_CAPACITY);

	if (cur_width >= FULL_CAPACITY) {

		qp.setPen(yellowColor);
		qp.setBrush(yellowColor);
		qp.drawRect(0, 0, full, 30);
		qp.setPen(redColor);
		qp.setBrush(redColor);
		qp.drawRect(full, 0, till - full, PANEL_HEIGHT);

	}
	else if (till > 0) {

		qp.setPen(yellowColor);
		qp.setBrush(yellowColor);
		qp.drawRect(0, 0, till, PANEL_HEIGHT);
	}

	QColor grayColor(90, 80, 60);
	qp.setPen(grayColor);

	for (int i = 1; i <= asize; i++) {

		qp.drawLine(i*step, 0, i*step, LINE_WIDTH);
		QFont newFont = font();
		newFont.setPointSize(7);
		setFont(newFont);

		QFontMetrics metrics(font());

		int w = metrics.width(num[i - 1]);
		qp.drawText(i*step - w / 2, DISTANCE, num[i - 1]);
	}
}

Burning::Burning(QWidget *parent)
	: QFrame(parent) {

	initUI();
}

void Burning::initUI() {

	const int MAX_VALUE = 750;
	cur_width = 0;

	slider = new QSlider(Qt::Horizontal, this);
	slider->setMaximum(MAX_VALUE);
	slider->setGeometry(50, 50, 130, 30);

	connect(slider, &QSlider::valueChanged, this, &Burning::valueChanged);

	QVBoxLayout *vbox = new QVBoxLayout(this);
	QHBoxLayout *hbox = new QHBoxLayout();

	vbox->addStretch(1);

	widget = new Widget(this);
	hbox->addWidget(widget, 0);

	vbox->addLayout(hbox);

	setLayout(vbox);
}

void Burning::valueChanged(int val) {

	cur_width = val;
	widget->repaint();
}

int Burning::getCurrentWidth() {

	return cur_width;
}
