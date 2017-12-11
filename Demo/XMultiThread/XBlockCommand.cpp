#include "XBlockCommand.h"
#include <QProcess>

XBlockCommand::XBlockCommand() :
	output(),
	error(),
	result(-1)
{

}

void XBlockCommand::exec(const QString& program, const QStringList& arguments)
{
	QProcess proc;
	proc.start(program, arguments);
	if (!proc.waitForStarted())
	{
		this->result = XBlockCommand::FailedToStart;
		return;
	}

	if (proc.waitForFinished())
	{
		// finished;
		if (proc.exitCode() == 0)
		{
			this->output = proc.readAllStandardOutput();
			this->result = XBlockCommand::Success;
		}
		else
		{
			this->error = proc.readAllStandardError();
			this->result = XBlockCommand::UnknownError;
		}
	}
	else
	{
		this->result = XBlockCommand::Timeout;
		proc.kill();
	}
}