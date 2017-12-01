#ifndef X_COMMAND_H
#define X_COMMAND_H

#include <QObject>
#include <QProcess>

class XCommand:public QObject{
    Q_OBJECT
public:
    XCommand(QObject* parent = Q_NULLPTR);
    void exec(const QString& program,const QStringList& arguments);

	const QString& getOutput()const { return output; }

signals:
	void errorOccurred(int errorCode);
	void finished(int exitCode);
public slots :
	void processFinished(int exitCode);
	void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
	QString output;
    
};


#endif