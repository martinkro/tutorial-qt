#ifndef PROTECTOR_PAGE_H
#define PROTECTOR_PAGE_H

#include "XBasePage.h"

class XTableView;
class XTreeView;

class ProtectorPage:public XBasePage
{
    Q_OBJECT
public:
    explicit ProtectorPage(QWidget* parent = 0);

protected:
    void showEvent(QShowEvent* e);

private:
    XTableView* tableView;
};


#endif