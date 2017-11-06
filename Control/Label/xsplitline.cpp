#include "xsplitline.h"

XSplitLine::XSplitLine(QWidget* parent,QFrame::Shape shape, int thick)
    :QFrame(parent)
{
	setFrameShadow(QFrame::Plain);
	setFrameShape(shape);
	if (shape == QFrame::HLine) {
		setFixedHeight(thick);
	}
	else if (shape == QFrame::VLine) {
		setFixedWidth(thick);
	}
}

