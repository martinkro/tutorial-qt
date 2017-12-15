#include "PackTool.h"
#include "quazip/quazip.h"
#include "quazip/quazipdir.h"
#include "quazip/quazipfile.h"

bool PackTool::isPacked(const QString& apkPath)
{
	QuaZip zip(apkPath);
	if (zip.open(QuaZip::mdUnzip))
	{
		bool a = zip.setCurrentFile("lib/armeabi/libtprt.so");
		bool b = zip.setCurrentFile("lib/armeabi-v7a/libtprt.so");
		bool c = zip.setCurrentFile("lib/x86/libtprt.so");
		if (a || b || c)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

QSet<QString> PackTool::getSoDllList(const QString& apkPath)
{
	QStringList ret;
	QuaZip zip(apkPath);
	if (zip.open(QuaZip::mdUnzip))
	{
		QuaZipDir dir(&zip);
		if (dir.cd("/lib/armeabi"))
		{
			ret += dir.entryList(QStringList()<<"*.so",QDir::Files);
		}
		if (dir.cd("/lib/armeabi-v7a"))
		{
			ret += dir.entryList(QStringList() << "*.so", QDir::Files);
		}
		if (dir.cd("/lib/x86"))
		{
			ret += dir.entryList(QStringList() << "*.so", QDir::Files);
		}
		if (dir.cd("/assets/bin/Data/Managed"))
		{
			ret += dir.entryList(QStringList() << "*.dll" << "*.DLL", QDir::Files);
		}

	}
	QSet<QString> set = ret.toSet();
	static QStringList FILTER_NAMES = QStringList() << "mscorlib.dll" << "UnityEngine.dll" << "System.dll" << "UnityEngine.UI.dll"
		<< "System.Core.dll"
		<< "libapollo_voice.so" << "libBugly.so" << "libgsdk.so"
		<< "libMSDK.so" << "libPandoraNet.so" << "libPandoraVideo.so"
		<< "libtpnsSecuirty.so"
		<< "libapollo.so";
	for (auto name : FILTER_NAMES)
	{
		auto it = set.find(name);
		if (it != set.end())
		{
			set.erase(it);
		}
	}
	return set;
}
