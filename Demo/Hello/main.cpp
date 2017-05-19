#include "TestQString.h"

#include <QtCore>
#include <iostream>
using namespace std;

void UnitTest()
{
	TestQString();
}

int main(int argc, char *argv[])
{
	cout << "Qt version: " << qVersion() << endl;

	UnitTest();

	return 0;
}
