#ifndef XSPLIT_LINE_H
#define XSPLIT_LINE_H

#include <QFrame>
class XSplitLine:public QFrame{
	Q_OBJECT
public:
    XSplitLine(QWidget* parent = Q_NULLPTR, QFrame::Shape shape=QFrame::HLine,int thick=1);

};

#endif