#ifndef XLOGGER_H
#define XLOGGER_H

#include <QObject>

class XLogger:public QObject
{
    Q_OBJECT
public:
    static XLogger& getInstance();

	static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message);
    
private:
    XLogger(QObject* parent = 0);
    
public:
    QString getLogFilePath()const;
    
private:
    QString logFilePath;
};

#endif