#include "historypage.h"
#include <QLabel>

HistoryPage::HistoryPage(QWidget* parent)
    :XBasePage(parent)
{
	new QLabel(tr("LABEL HISTORY"), this);
}