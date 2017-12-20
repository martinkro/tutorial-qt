#ifndef NUMBER_THREAD_H
#define NUMBER_THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class NumberThread:public QThread
{
    Q_OBJECT
public:
	NumberThread(QObject* parent = 0);
	~NumberThread();

signals:
	void valueChanged(int value);

public:
	void startThread();
	void stopThread();

protected:
	void run()override;

public:
	QMutex mutex;
	QWaitCondition condition;
	QAtomicInt stop;
	QAtomicInt abort;
};

#endif