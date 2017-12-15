#ifndef PACK_TOOL_H
#define PACK_TOOL_H

#include <QObject>
#include <QStringList>
#include <QSet>
#include <QString>

class PackTool:public QObject
{
    Q_OBJECT
public:
    PackTool(QObject* parent = Q_NULLPTR);

public:
	static bool isPacked(const QString& apkPath);
	static QSet<QString> getSoDllList(const QString& apkPath);
};

#endif