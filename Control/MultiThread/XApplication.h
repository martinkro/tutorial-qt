#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include <QtWidgets/QApplication>

class XApplication:public QApplication
{
    Q_OBJECT
public:
	XApplication(int &argc, char **argv);
	virtual ~XApplication();
};

#endif