#include "gamelistitemview.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

GameListItemView::GameListItemView(QWidget *parent)
	: QWidget(parent)
{
	m_icon = new QLabel;
	QPixmap pixmap("sgame.png");
	m_icon->setPixmap(pixmap);
	m_title = new QLabel(tr("Title"));
	m_desc = new QLabel(tr("xxxxx xxxxxxx"));

	QVBoxLayout* c2 = new QVBoxLayout;
	c2->addWidget(m_title);
	c2->addWidget(m_desc);
	QHBoxLayout* main = new QHBoxLayout;
	main->addWidget(m_icon);
	main->addLayout(c2);
	main->addStretch();
	setLayout(main);
}

GameListItemView::~GameListItemView()
{
}

void GameListItemView::paintEvent(QPaintEvent* event) {
	QWidget::paintEvent(event);
}
