#include "label.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "xsplitline.h"
#include <QFrame>

Label::Label(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QLabel* labelTitle2 = new QLabel(tr("Title2"));
	QLabel* labelContent2 = new QLabel(tr("Content2"));
	XSplitLine* splitH1 = new XSplitLine;
	splitH1->setObjectName("splitH1");
	

	QVBoxLayout* c1 = new QVBoxLayout;
	c1->addWidget(labelTitle2);
	c1->addWidget(splitH1);
	c1->addWidget(labelContent2,1);

	QLabel* labelTitle1 = new QLabel(tr("Title1"));
	QLabel* labelContent1 = new QLabel(tr("Content1"));
	labelContent1->setAlignment(Qt::AlignTop);
	XSplitLine* splitH2 = new XSplitLine;
	splitH2->setObjectName("splitH2");
	QVBoxLayout* c2 = new QVBoxLayout;
	c2->addWidget(labelTitle1);
	c2->addWidget(splitH2);
	c2->addWidget(labelContent1, 1);

	QHBoxLayout* main = new QHBoxLayout;
	XSplitLine* splitv = new XSplitLine(Q_NULLPTR,QFrame::VLine);
	
	splitv->setObjectName("splitv");
	
	main->addLayout(c1,7);
	main->addWidget(splitv);
	main->addLayout(c2,3);
	setLayout(main);

	resize(900, 600);

}
