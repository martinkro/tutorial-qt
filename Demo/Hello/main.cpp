#include "TestQString.h"
#include "TestQDateTime.h"
#include "TestContainers.h"

#include <QtCore>
#include <iostream>
using namespace std;

void UnitTest()
{
	TestQString();
	TestQDateTime();
	TestQContainers();

}

int main(int argc, char *argv[])
{
	cout << "Qt version: " << qVersion() << endl;

	UnitTest();

	return 0;
}
