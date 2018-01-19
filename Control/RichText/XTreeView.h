#ifndef XTREEVIEW_H
#define XTREEVIEW_H

#include <QTreeView>

class XTreeView:public QTreeView
{
    Q_OBJECT
public:
    explicit XTreeView(QWidget* parent = 0);
    
};


#endif