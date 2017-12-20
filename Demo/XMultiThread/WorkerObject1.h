#ifndef WORKER_OBJECT1_H
#define WORKER_OBJECT1_H

#include <QObject>

class WorkerObject1:public QObject
{
    Q_OBJECT
public:
	WorkerObject1(QObject* parent = 0);

public slots:
	void onDoWork1(const QString& message);

signals:
	void work1Done(const QString& message);
};

#endif