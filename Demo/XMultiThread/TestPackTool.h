#ifndef TEST_PACK_TOOL_H
#define TEST_PACK_TOOL_H

#include <QObject>

class TestPackTool:public QObject
{
    Q_OBJECT
private slots:
    void testIsPacked();
};

#endif