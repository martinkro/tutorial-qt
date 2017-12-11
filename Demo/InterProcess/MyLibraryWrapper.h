#ifndef MY_LIBRARY_WRAPPER_H
#define MY_LIBRARY_WRAPPER_H

#include <QThread>

class QPushButton;
class MyLibraryWrapper:public QThread
{
    Q_OBJECT
public:
    MyLibraryWrapper();
protected:
   void run();
signals:
   void done(const QString &results);
   void do_finished();
private slots:
   void doTheWork();


};


#endif