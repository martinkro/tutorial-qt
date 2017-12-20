#ifndef WORK_CONTROLLER_H
#define WORK_CONTROLLER_H

#include <QObject>
#include <QThread>

class WorkController:public QObject
{
    Q_OBJECT
public:
	WorkController(QObject* parent = 0);
	~WorkController();

public slots:
	void onWork1Done(const QString& message);

signals:
	void doWork1(const QString& message);

public:
	void test();

private:
	QThread workerThread;
};

#endif