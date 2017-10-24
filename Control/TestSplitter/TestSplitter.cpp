#include "TestSplitter.h"
#include <QLabel>
#include <QSplitter>
#include <QHBoxLayout>

TestSplitter::TestSplitter(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QLabel* A = new QLabel(tr("A"));
	A->setObjectName("a");
	QLabel* B = new QLabel(tr("B"));
	B->setObjectName("b");

	QSplitter* splitter = new QSplitter(Qt::Horizontal);
	splitter->setObjectName("splitter");
	splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	splitter->addWidget(A);
	splitter->addWidget(B);
	splitter->setStretchFactor(0, 7);
	splitter->setStretchFactor(1, 3);
	splitter->handle(1)->setDisabled(true);

	QHBoxLayout* main = new QHBoxLayout;
	main->addWidget(splitter);

	setLayout(main);

	resize(900, 600);
}
