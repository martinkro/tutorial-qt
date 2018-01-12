#ifndef XDIALOGBASE_H
#define XDIALOGBASE_H

#include <QDialog>

class XDialogBase:public QDialog
{
    Q_OBJECT
public:
    explicit XDialogBase(QWidget* parent = 0);

protected:
    void paintEvent(QPaintEvent* event)override;
};


#endif