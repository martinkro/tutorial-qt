#pragma once

#include <QWidget>
#include "ui_sortlistview.h"

class SortListView : public QWidget, public Ui::SortListView
{
	Q_OBJECT

public:
	SortListView(QWidget *parent = Q_NULLPTR);
	~SortListView();
};
