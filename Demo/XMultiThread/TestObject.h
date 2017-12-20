#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H


#include <QObject>
class TestObject:public QObject
{
    Q_OBJECT
public:
	TestObject(QObject* parent = 0);

private slots:
	void onShowMessage();
    
};


#endif