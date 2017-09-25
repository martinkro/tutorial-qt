#include "signaturepage.h"
#include <QLabel>

SignaturePage::SignaturePage(QWidget* parent)
    :XBasePage(parent)
{
	new QLabel(tr("LABEL SIGNATURE"), this);
}