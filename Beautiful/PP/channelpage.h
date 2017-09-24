#ifndef CHANNEL_PAGE_H
#define CHANNEL_PAGE_H

#include "basepage.h"

class ChannelPage :public XBasePage
{
	Q_OBJECT
public:
	explicit ChannelPage(QWidget* parent = Q_NULLPTR);
	virtual ~ChannelPage() {}
};

#endif