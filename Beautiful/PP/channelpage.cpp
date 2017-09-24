#include "channelpage.h"
#include <QLabel>

ChannelPage::ChannelPage(QWidget* parent)
	:XBasePage(parent)
{
	new QLabel(tr("LABEL CHANNEL"), this);
}