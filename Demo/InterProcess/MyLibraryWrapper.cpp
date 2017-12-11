#include "MyLibraryWrapper.h"
#include <QTimer>
#include <QDebug>

MyLibraryWrapper::MyLibraryWrapper() : QThread()
{
  // We have to do this to make sure our thread has the
  // correct affinity.
  //moveToThread(this);
  connect(this, &QThread::finished, [=] {
	  qDebug() << "[do_finished]ThreadId:" << QThread::currentThreadId();
	  emit do_finished();
  });
  // This will do nothing until the user calls start().
}

void MyLibraryWrapper::run()
{
  // This schedules the doTheWork() function
  // to run just after our event loop starts up
  //QTimer::singleShot(0, this, SLOT(doTheWork()));
	doTheWork();
  // This starts the event loop. Note that
  // exec() does not return until the
  // event loop is stopped.
  //exec();    
}

void MyLibraryWrapper::doTheWork()
{

	qDebug() << "[DoTheWork]ThreadId:" << QThread::currentThreadId();
  // Do the heavy-duty blocking stuff here
  // (simulated by a 5 second sleep for
  // this example)
  //sleep(5);

  // When you're done, emit the results:
  emit done("First job's finished.");
  
  // And some more sleeping for fun
  sleep(1);
  emit done("Second job's finished.");

  // ...
}