#include "XApplication.h"
#include "XLogger.h"

XApplication::XApplication(int &argc, char **argv) :
	QApplication(argc, argv)
{
	qInstallMessageHandler(XLogger::messageHandler);
}

XApplication::~XApplication()
{

}