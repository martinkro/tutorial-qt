#include "xsplitline.h"

XSplitLine::XSplitLine(QWidget* parent)
    :QFrame(parent)
{

    setHorizontalVertical(0);
}

int XSplitLine::setHorizontalVertical(int i)
{
    if (i == 0)
    {
        setFrameShape(QFrame::HLine); 
        setFrameShadow(QFrame::Plain);
		
       // setSizeRect(30,30,100,20);
    }
    else if (i == 1)
    {
        setFrameShape(QFrame::VLine); 
		setFrameShadow(QFrame::Plain);
        //setSizeRect(30,30,20,100);
    }
	return i;
}

void XSplitLine::setSizeRect( int x, int y, int w, int h)
{
    setGeometry(QRect(x,y,w,h));
}