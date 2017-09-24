#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <QWidget>

class XBasePage:public QWidget
{
	Q_OBJECT
public:
	explicit XBasePage(QWidget* parent = Q_NULLPTR);
	virtual ~XBasePage() {}

};

#endif