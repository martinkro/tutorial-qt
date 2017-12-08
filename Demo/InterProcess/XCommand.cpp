#include "XCommand.h"
#include <QProcess>
#include <QDebug>

XCommand::XCommand(QObject* parent)
	:QObject(parent)
{
	//ShellExecute
	output.clear();
}

void XCommand::exec(const QString& program, const QStringList& arguments)
{
	QProcess* proc = new QProcess(this);
	connect(proc, &QProcess::errorOccurred, [=](QProcess::ProcessError error) {
		qDebug() << "Process error:" << error;
		emit errorOccurred(error);
	});
	connect(proc, SIGNAL(finished(int exitCode)),this,SLOT(finished(int exitCode)));
	connect(proc, SIGNAL(finished(int exitCode, QProcess::ExitStatus exitStatus)), this, SLOT(finished(int exitCode, QProcess::ExitStatus exitStatus)));
	connect(proc, &QProcess::readyReadStandardError, [=]() {
		qDebug() << "Process ready stderr";
	});
	connect(proc, &QProcess::readyReadStandardOutput, [=]() {
		qDebug() << "Process read stdout";
		output = proc->readAllStandardOutput();
	});
	connect(proc, &QProcess::started, [=]() {
		qDebug() << "Process started";
	});
	connect(proc, &QProcess::stateChanged, [=](QProcess::ProcessState newState) {
		qDebug() << "Process state:" << newState;
	});

	proc->start(program, arguments);
}

void XCommand::processFinished(int exitCode)
{
	qDebug() << "Process exit code:" << exitCode;
	emit finished(exitCode);
}

void XCommand::processFinished(int exitCode,QProcess::ExitStatus exitStatus)
{
	qDebug() << "Process exit code:" << exitCode << "|exit status:" << exitStatus;
	emit finished(exitCode);
}