#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class GameListItemView : public QWidget
{
	Q_OBJECT

public:
	GameListItemView(QWidget *parent = Q_NULLPTR);
	~GameListItemView();

protected:
	void paintEvent(QPaintEvent* event);

private:
	QLabel* m_icon;
	QLabel* m_title;
	QLabel* m_desc;
};
