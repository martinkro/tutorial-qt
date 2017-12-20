#ifndef TRANSACTION_THREAD_H
#define TRANSACTION_THREAD_H

#include <QThread>

class TransactionThread:public QThread
{
    Q_OBJECT
public:
	TransactionThread(QObject* parent = 0);
	~TransactionThread();
};

#endif