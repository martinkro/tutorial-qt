#ifndef ADVANCE_CONFIG_DIALOG_H
#define ADVANCE_CONFIG_DIALOG_H

#include "XDialogBase.h"

class AdvanceConfigDialog:public XDialogBase
{
    Q_OBJECT
public:
    explicit AdvanceConfigDialog(QWidget* parent = 0);
};

#endif