#include <QtCore/QCoreApplication>
#include <QDebug>

#include "ApkParser.h"
#include "MultiChannelTool.h"
#include "MultiChannelWorker.h"

#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include "quazip/quazipdir.h"

#include "PackTool.h"
#include "TestPackTool.h"
#include "TestObject.h"
#include "WorkController.h"

#include <QtTest/QtTest>
#include <QElapsedTimer>
#include <QProcess>

// 进程间通信
// 多线程
// 序列化

class XFuncPerformance
{
public:
	XFuncPerformance(const QString& name) :
		name(name)
	{
		timer.start();
	}

	~XFuncPerformance()
	{
		qDebug() << "[" << name << "]time:" << timer.elapsed() << "ms.";
	}

private:
	QElapsedTimer timer;
	QString name;
};

void testPackTool(const QCoreApplication& app)
{
	int err = 0;
	TestPackTool testPackTool;
	err = qMax(err, QTest::qExec(&testPackTool, app.arguments()));
	qDebug() << "error:" << err;
}

class ZipFileTreeNode
{
public:
	ZipFileTreeNode(const QString& filename,const QString& fullpath,ZipFileTreeNode* p) :
		filename(filename),
		fullpath(fullpath),
		parent(p)
	{
		if (parent)
		{
			parent->children.append(this);
		}
	}

	~ZipFileTreeNode()
	{
		qDeleteAll(children);
	}

	void setParent(ZipFileTreeNode* p)
	{
		if (p == nullptr || parent == p || parent) return;
		parent = p;
		parent->children.append(this);
	}

public:
	ZipFileTreeNode* tryGetChild(const QString& name)const
	{
		ZipFileTreeNode* ret = nullptr;
		for (auto child : children)
		{
			if (child->filename.compare(name) == 0)
			{
				ret = child;
				break;
			}
		}
		return ret;
	}
	void dump(int indent)
	{

		//qDebug() << QString(indent,' ') + fullpath;
		for (auto child : children)
		{
			child->dump(indent + 2);
		}
	}

	bool hasChildren()const
	{
		return children.size() > 0;
	}

	void totalCount(int& out)
	{
		if (hasChildren())
		{
			for (auto child : children)
			{
				child->totalCount(out);
			}
		}
		else
		{
			out++;
		}
	}

public:
	QString getFullPath()const {
		if (fullpath == "/") return "";
		else return fullpath;
	}
public:
	QString filename;
	QString fullpath;
	ZipFileTreeNode* parent;
	QList<ZipFileTreeNode*> children;
};

class ZipFileTree
{
public:
	ZipFileTree(const QStringList& names) :
		root(nullptr)
	{
		root = new ZipFileTreeNode("/","/",nullptr);
		load2(names);
	}

	void load1(const QStringList& names)
	{
		for (auto name : names)
		{
			QStringList splits = name.split(QString("/"));
			ZipFileTreeNode* p = root;
			for (auto item : splits)
			{
				ZipFileTreeNode* node = p->tryGetChild(item);
				if (node == nullptr)
				{
					node = new ZipFileTreeNode(item,"", p);
				}
				p = node;
			}
		}
	}

	void recursiveBuildNode2(QHash<QString, ZipFileTreeNode*>& mapNameNodes, const QStringList& splits, int count,ZipFileTreeNode* currentNode)
	{
		auto fGenFullPath = [](const QStringList& names, int count)->QString {
			QString ret = "";
			for (int k = 0; k < count; k++)
			{
				ret = ret + names.at(k);
				if (k != count - 1)
				{
					ret += "/";
				}
			}
			return ret;
		};
		if (count == 0)
		{
			currentNode->setParent(root);
		}
		else
		{
			const QString& filename = splits.at(count - 1);
			QString fullpath = fGenFullPath(splits, count);
			auto it = mapNameNodes.find(fullpath);
			if (it != mapNameNodes.end())
			{
				currentNode->setParent(it.value());
			}
			else
			{
				// 没找到？
				ZipFileTreeNode* node = new ZipFileTreeNode(filename,fullpath, nullptr);
				recursiveBuildNode2(mapNameNodes, splits, count - 1, node);
				currentNode->setParent(node);
				mapNameNodes.insert(fullpath, node);
			}
		}
	}

	void load2(const QStringList& names)
	{
		QHash<QString, ZipFileTreeNode*> mapNameNodes;
		for (auto name : names)
		{
			QStringList splits = name.split(QString("/"));
			int count = splits.size();
			ZipFileTreeNode* node = new ZipFileTreeNode(splits.at(count-1), name, nullptr); // name 是全路径
			recursiveBuildNode2(mapNameNodes, splits, count - 1, node);
		}
	}
		
	~ZipFileTree()
	{
		delete root;
	}

public:
	void dump()
	{
		root->dump(0);
		int count = 0;
		root->totalCount(count);
		qDebug() << count << " files";
		
	}

private:
	ZipFileTreeNode* root;
};

void convertZipToTree(const QString& zipPath)
{
	XFuncPerformance perf(__FUNCTION__);
	QuaZip zip(zipPath);
	if (zip.open(QuaZip::mdUnzip))
	{
		QStringList names = zip.getFileNameList();
		ZipFileTree tree(names);
		tree.dump();
	}
}

void testQuazip()
{
	QString zipPath = "f:/Game/cf-20170803.apk";
	QuaZip zip(zipPath);
	if (zip.open(QuaZip::mdUnzip))
	{
		QuaZipDir dir(&zip, "/");
		QList<QuaZipFileInfo> infos = dir.entryInfoList();
		infos = zip.getFileInfoList();
		for(auto info:infos)
		{
			qDebug() << info.name << ":" << info.flags << ":" << info.uncompressedSize;
		}

		QStringList names = dir.entryList();
		for (auto name : names)
		{
			qDebug() << name;
		}
	}
	QSet<QString> x = PackTool::getSoDllList("f:/Game/cf-20170803.apk");
	for (auto name : x)
	{
		qDebug() << name;
	}
	//QuaZip zip("f:/Game/cf-20170803.apk");
	//if (zip.open(QuaZip::mdUnzip))
	//{
	//	QStringList names = zip.getFileNameList();
	//	for (auto name : names)
	//	{
	//		//qDebug() << name;
	//	}

	//	bool ok = zip.setCurrentFile("lib/armeabi-v7a/libtersafe.so");
	//	if (ok)
	//	{
	//		qDebug() << "/lib/armeabi-v7a exists";
	//	}
	//	else
	//	{
	//		qDebug() << zip.getZipError();
	//	}


	//	QuaZipDir dir(&zip, "/");
	//	if (dir.cd("/lib/armeabi"))
	//	{
	//		QStringList names = dir.entryList(QStringList()<<".so",QDir::Files);
	//		for (auto name : names)
	//		{
	//			qDebug() << name;
	//		}
	//	}
	//	if (dir.cd("/lib/armeabi-v7a"))
	//	{
	//		QStringList names = dir.entryList(QStringList() << ".so", QDir::Files);
	//		for (auto name : names)
	//		{
	//			qDebug() << name;
	//		}
	//	}
	//	if (dir.cd("/lib/x86"))
	//	{
	//		QStringList names = dir.entryList(QStringList() << ".so", QDir::Files);
	//		for (auto name : names)
	//		{
	//			qDebug() << name;
	//		}
	//	}
	//	if (dir.exists())
	//	{
	//		qDebug() << "Dir name:" << dir.dirName();
	//		qDebug() << "Dir count:" << dir.count();

	//		QStringList names = dir.entryList();
	//		for (auto name : names)
	//		{
	//			qDebug() << name;
	//		}
	//	}
	//	else
	//	{
	//		qDebug() << "Not exists";
	//	}
	//}
}



void testAllCase(const QCoreApplication& app)
{
	//testQuazip();
	//testPackTool(app);
	convertZipToTree("f:/Game/cf-20170803.apk");
	//convertZipToTree("f:/Game/cf-20170803.apk");
	//convertZipToTree("f:/Game/SwordGame.apk");
}

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qRegisterMetaType<MApkInfo>();

	//{
	//	testAllCase(a);
	//}

	QString apkPath = "C:\\Users\\sundayliu\\Desktop\\MTPClient -20171227\\download\\3843_SwordGame.unsigned.shell.apk";
	//apkPath = '"' + apkPath + '"';
	qDebug() << apkPath;
	QString cmd = "explorer.exe /select," + apkPath;
	QProcess::startDetached(cmd);

	qDebug() << "===Test Object[===";
	TestObject testObject;
	qDebug() << "===Test Object]===";

	qDebug() << "===Test WorkController[===";
	WorkController workController;
	workController.test();
	qDebug() << "===Test WorkController]===";

	QString spaces(4, ' ');
	qDebug() << spaces;



#ifdef QT_DEBUG
	cout << "Debug mode" << endl;
	qDebug() << "Debug mode";
#else
	cout << "Release mode" << endl;
	qDebug() << "Release mode";
	//qErrnoWarning << "Release mode";
#endif

	//{
	//	MultiChannelTool* t = new MultiChannelTool("f:/Game/MultiChannel", "f:/Game/MultiChannel/o");
	//	//t->exec();
	//	t->execForThread();
	//	QObject::connect(t, &MultiChannelTool::prepare_finished, [&](int total, int success) {
	//		qDebug() << total << ":" << success;
	//		delete t;
	//	});
	//}

	//qDebug() << "Test MultiThread";

	//ApkParser* apkParser = new ApkParser(qApp);;
	//QObject::connect(apkParser, &ApkParser::parseFinished, [=](int exitCode) {

	//	qDebug() << "Exit Code:" << exitCode;
	//	qDebug() << apkParser->getAppName();
	//	qDebug() << apkParser->getAppVersion();
	//	qDebug() << apkParser->getPackageName();
	//	if (exitCode == 0)
	//	{
	//		apkParser->startParse("f:/Game/7577/t.txt");
	//	}
	//	
	//});
	//apkParser->startParse("f:/Game/7577/test.apk");

	//qDebug() << "Test END";
	//QString strEnd = "QString END.";
	//qDebug() << strEnd;

	return a.exec();
}
