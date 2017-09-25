#ifndef HISTORY_PAGE_H
#define HISTORY_PAGE_H

#include "basepage.h"

class HistoryPage:public XBasePage
{
    Q_OBJECT
public:
    explicit HistoryPage(QWidget* parent = Q_NULLPTR);
    virtual ~HistoryPage(){}
};

#endif