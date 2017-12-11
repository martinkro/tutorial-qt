#ifndef X_BLOCK_COMMAND_H
#define X_BLOCK_COMMAND_H

#include <QString>

class XBlockCommand
{
public:
	enum CommandResult{
		Success = 0,
		UnknownError = -1,
		FailedToStart = -2,
		Timeout = -3,

	};
public:
	XBlockCommand();

	void exec(const QString& program, const QStringList& arguments);
public:
	const QString& getOutput()const { return output; }
	const QString& getError()const { return error; }
	bool isSuccess()const { return result == XBlockCommand::Success; }
private:
	QString output;
	QString error;
	int result;
};


#endif