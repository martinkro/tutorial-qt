#ifndef TEST_PAGE_H
#define TEST_PAGE_H

#include "XBasePage.h"

class TestPage:public XBasePage
{
    Q_OBJECT
public:
    explicit TestPage(QWidget* parent = 0);

    QString getHelpInfo();
};


#endif