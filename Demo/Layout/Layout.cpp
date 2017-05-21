#include "Layout.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QTextEdit>

Layout::Layout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Layouts::Layouts(QWidget *parent)
	: QWidget(parent) {

	QVBoxLayout *vbox = new QVBoxLayout();
	QHBoxLayout *hbox = new QHBoxLayout(this);

	QListWidget *lw = new QListWidget(this);
	lw->addItem("The Omen");
	lw->addItem("The Exorcist");
	lw->addItem("Notes on a scandal");
	lw->addItem("Fargo");
	lw->addItem("Capote");

	QPushButton *add = new QPushButton("Add", this);
	QPushButton *rename = new QPushButton("Rename", this);
	QPushButton *remove = new QPushButton("Remove", this);
	QPushButton *removeall = new QPushButton("Remove All", this);

	vbox->setSpacing(3);
	vbox->addStretch(1);
	vbox->addWidget(add);
	vbox->addWidget(rename);
	vbox->addWidget(remove);
	vbox->addWidget(removeall);
	vbox->addStretch(1);

	hbox->addWidget(lw);
	hbox->addSpacing(15);
	hbox->addLayout(vbox);

	setLayout(hbox);
}

FormEx::FormEx(QWidget *parent)
	: QWidget(parent) {

	QLineEdit *nameEdit = new QLineEdit(this);
	QLineEdit *addrEdit = new QLineEdit(this);
	QLineEdit *occpEdit = new QLineEdit(this);

	QFormLayout *formLayout = new QFormLayout;
	formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
	formLayout->addRow("Name:", nameEdit);
	formLayout->addRow("Email:", addrEdit);
	formLayout->addRow("Age:", occpEdit);

	setLayout(formLayout);
}

Calculator::Calculator(QWidget *parent)
	: QWidget(parent) {

	QGridLayout *grid = new QGridLayout(this);
	grid->setSpacing(2);

	QList<QString> values({ "7", "8", "9", "/",
		"4", "5", "6", "*",
		"1", "2", "3", "-",
		"0", ".", "=", "+"
	});

	int pos = 0;

	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {

			QPushButton *btn = new QPushButton(values[pos], this);
			btn->setFixedSize(40, 40);
			grid->addWidget(btn, i, j);
			pos++;
		}
	}

	setLayout(grid);
}

Review::Review(QWidget *parent)
	: QWidget(parent) {

	QGridLayout *grid = new QGridLayout(this);
	grid->setVerticalSpacing(15);
	grid->setHorizontalSpacing(10);

	QLabel *title = new QLabel("Title:", this);
	grid->addWidget(title, 0, 0, 1, 1);
	title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QLineEdit *edt1 = new QLineEdit(this);
	grid->addWidget(edt1, 0, 1, 1, 1);

	QLabel *author = new QLabel("Author:", this);
	grid->addWidget(author, 1, 0, 1, 1);
	author->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QLineEdit *edt2 = new QLineEdit(this);
	grid->addWidget(edt2, 1, 1, 1, 1);

	QLabel *review = new QLabel("Review:", this);
	grid->addWidget(review, 2, 0, 1, 1);
	review->setAlignment(Qt::AlignRight | Qt::AlignTop);

	QTextEdit *te = new QTextEdit(this);
	grid->addWidget(te, 2, 1, 3, 1);

	setLayout(grid);
}
