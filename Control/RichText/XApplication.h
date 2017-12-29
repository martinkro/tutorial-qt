#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include <QtWidgets/QApplication>

class QTranslator;

class XApplication:public QApplication
{
    Q_OBJECT
public:
	XApplication(int &argc, char **argv);
	virtual ~XApplication();

private:
	void initialize();

private:
	void intializeTranslator();
	void intializeStyleSheet();
	void intializeFonts();

private:
	QTranslator* translator;
};

#endif