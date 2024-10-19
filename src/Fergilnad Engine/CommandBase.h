// Command Base

#ifndef _CommandBase
#define _CommandBase

class CommandBase
{
public:
	CommandBase() {};
	CommandBase(const CommandBase& other) = default;
	CommandBase& operator=(const CommandBase& other) = default;
	virtual ~CommandBase() {};

	virtual void Execute() {};
};

#endif _CommandBase