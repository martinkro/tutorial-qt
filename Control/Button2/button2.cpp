#include "button2.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>

Button2::Button2(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_pushbutton = new QPushButton(tr("QPushButton"));
	m_toolbutton = new QToolButton;
	m_toolbutton->setText(tr("QToolButton"));

	

	QToolButton* toolbar1 = new QToolButton;
	toolbar1->setObjectName("toolbar1");
	toolbar1->setText(tr("toolbar1"));
	//toolbar1->setAutoExclusive(true);
	toolbar1->setCheckable(true);
	toolbar1->setChecked(true);
	toolbar1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(toolbar1, &QToolButton::clicked, [=]() {
		toolbar1->setChecked(true);
	});

	QToolButton* toolbar2 = new QToolButton;
	toolbar2->setObjectName("toolbar2");
	toolbar2->setText(tr("toolbar2"));
	//toolbar2->setAutoExclusive(true);
	toolbar2->setCheckable(true);
	toolbar2->setChecked(false);
	toolbar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(toolbar2, &QToolButton::clicked, [=]() {
		toolbar2->setChecked(true);
	});

	QToolButton* toolbar3 = new QToolButton;
	toolbar3->setObjectName("toolbar3");
	toolbar3->setText(tr("toolbar3"));
	//toolbar3->setAutoExclusive(true);
	toolbar3->setCheckable(true);
	toolbar3->setChecked(false);
	toolbar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(toolbar3, &QToolButton::clicked, [=]() {
		toolbar3->setChecked(true);
	});

	QButtonGroup* group = new QButtonGroup(this);
	group->setExclusive(true);
	group->addButton(toolbar1);
	group->addButton(toolbar2);
	group->addButton(toolbar3);

	QHBoxLayout* toolbar = new QHBoxLayout;
	toolbar->addWidget(toolbar1);
	toolbar->addWidget(toolbar2);
	toolbar->addWidget(toolbar3);

	QVBoxLayout* v = new QVBoxLayout;
	v->addLayout(toolbar);
	v->addWidget(m_pushbutton);
	v->addWidget(m_toolbutton);
	

	setLayout(v);
}
