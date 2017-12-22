#include "MultiThread.h"
#include "XApplication.h"

int main(int argc, char *argv[])
{
	XApplication a(argc, argv);
	MultiThread w;
	w.show();
	return a.exec();
}
