#include "XCommand.h"
#include <QProcess>
#include <QDebug>

XCommand::XCommand(QObject* parent)
	:QObject(parent)
{
	qDebug() << "XCommand constructor";
	output.clear();
	error.clear();
	proc = new QProcess(this);

	connect(proc, &QProcess::errorOccurred, [=](QProcess::ProcessError error) {
		qDebug() << "Process error:" << error;
		emit proc_errorOccurred(error);
	});

	connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus) {
		onProcessFinished(exitCode, exitStatus);
	});
	connect(proc, &QProcess::readyReadStandardError, [=]() {
		qDebug() << "Process ready stderr";
		QString data = proc->readAllStandardError();
		error += data;
	});
	connect(proc, &QProcess::readyReadStandardOutput, [=]() {
		qDebug() << "Process read stdout";
		QString data = proc->readAllStandardOutput();
		output += data;
	});
	connect(proc, &QProcess::started, [=]() {
		qDebug() << "Process started";
	});
	connect(proc, &QProcess::stateChanged, [=](QProcess::ProcessState newState) {
		qDebug() << "Process state:" << newState;
	});
}

bool XCommand::isRunning()
{
	return proc->state() != QProcess::NotRunning;
}

XCommand::~XCommand()
{
	qDebug() << "XCommand destructor";
}

void XCommand::exec(const QString& program, const QStringList& arguments)
{
	output.clear();
	error.clear();
	proc->start(program, arguments);
}

void XCommand::onProcessFinished(int exitCode)
{
	qDebug() << "Process exit code:" << exitCode;
	emit proc_finished(exitCode);
}

void XCommand::onProcessFinished(int exitCode,QProcess::ExitStatus exitStatus)
{
	qDebug() << "Process exit code:" << exitCode << "|exit status:" << exitStatus;
	emit proc_finished(exitCode);
}