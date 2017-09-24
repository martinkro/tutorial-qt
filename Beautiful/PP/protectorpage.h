#ifndef PROTECTOR_PAGE_H
#define PROTECTOR_PAGE_H

#include "basepage.h"

class ProtectorPage:public XBasePage
{
	Q_OBJECT
public:
	explicit ProtectorPage(QWidget* parent = Q_NULLPTR);
	virtual ~ProtectorPage() {}

};

#endif