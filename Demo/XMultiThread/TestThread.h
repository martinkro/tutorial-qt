#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include <QThread>

class TestThread:public QThread
{
    Q_OBJECT
public:
	TestThread(QObject* parent = 0);

signals:
	void showMessage();

protected:
	void run()override;
};


#endif