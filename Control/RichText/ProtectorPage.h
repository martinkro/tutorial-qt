#ifndef PROTECTOR_PAGE_H
#define PROTECTOR_PAGE_H

#include "XBasePage.h"

class ProtectorPage:public XBasePage
{
    Q_OBJECT
public:
    explicit ProtectorPage(QWidget* parent = 0);
};


#endif