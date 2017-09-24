#include "protectorpage.h"
#include <QLabel>

ProtectorPage::ProtectorPage(QWidget* parent)
	:XBasePage(parent)
{
	new QLabel(tr("PROTECTOR"), this);
}