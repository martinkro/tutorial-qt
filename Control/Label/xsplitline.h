#ifndef XSPLIT_LINE_H
#define XSPLIT_LINE_H

#include <QFrame>
class XSplitLine:public QFrame{
    Q_OBJECT
public:
    XSplitLine(QWidget* parent = Q_NULLPTR);
public slots:
    int setHorizontalVertical( int i=0 );
    void setSizeRect( int x=0, int y=0, int w=100, int h=30);
};

#endif