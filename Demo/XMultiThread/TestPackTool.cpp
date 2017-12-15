#include "TestPackTool.h"
#include "PackTool.h"

#include <QtTest/QtTest>

void TestPackTool::testIsPacked()
{
	QCOMPARE(PackTool::isPacked("f:/Game/cf-20170803.apk"), false);
	QCOMPARE(PackTool::isPacked("f:/Game/SwordGame.apk"), false);
	QCOMPARE(PackTool::isPacked("f:/Game/cf.shell.apk"), true);
}