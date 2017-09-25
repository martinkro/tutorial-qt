#ifndef SIGNATURE_PAGE_H
#define SIGNATURE_PAGE_H

#include "basepage.h"

class SignaturePage:public XBasePage
{
  Q_OBJECT
public:
    explicit SignaturePage(QWidget* parent = Q_NULLPTR);
    virtual ~SignaturePage(){}
};

#endif