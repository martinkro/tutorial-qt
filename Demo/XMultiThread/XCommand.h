#ifndef X_COMMAND_H
#define X_COMMAND_H

#include <QObject>
#include <QProcess>

class XCommand:public QObject{
    Q_OBJECT
public:
    XCommand(QObject* parent = Q_NULLPTR);
	virtual ~XCommand();
    void exec(const QString& program,const QStringList& arguments);

	const QString& getOutput()const { return output; }
	const QString& getError()const { return error; }

	bool isRunning();

signals:
	void proc_errorOccurred(int errorCode);
	void proc_finished(int exitCode);
public slots :
	void onProcessFinished(int exitCode);
	void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
	QString output;
	QString error;
	QProcess* proc;
    
};


#endif