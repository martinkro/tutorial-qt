#include "RichText.h"
#include "XApplication.h"
#include <QtWidgets/QApplication>

#include <iostream>
using namespace std;
class A
{
public:
	void print()
	{
		cout << "A constructor 2" << endl;
	}
};
int main(int argc, char *argv[])
{
	XApplication a(argc, argv);
	RichText w;
	w.show();

	A t;
	t.print();
	return a.exec();
}
