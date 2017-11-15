#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QString>

#include <memory>
#include <map>
#include <iostream>

using namespace std;

class A {
public:
	A()
	{
		cout << "A" << endl;
	}

	~A() {
		cout << "~A" << endl;
	}
};

using AMap = map<int, shared_ptr<A>>;
void test_map(AMap& map)
{
	cout << "test map s===" << endl;
	map.insert(make_pair(1, make_shared<A>()));
	map.insert(make_pair(2, make_shared<A>()));
	cout << "test map e===" << endl;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "Hello";

	qreal b = 63.23456;
	QString text = QString::number(b,'f',1);
	qDebug() << text;

	AMap map;
	test_map(map);
	cout << "remove 1" << endl;
	map.erase(1);
	cout << "remove 2" << endl;
	map.clear();
	cout << "remove e" << endl;
	return 0;

	//return a.exec();
}
