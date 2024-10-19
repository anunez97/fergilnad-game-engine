// Scene Registration Broker

#include "SceneRegistrationBroker.h"
#include "CommandBase.h"

void SceneRegistrationBroker::addCommand(CommandBase* cmd)
{
	lstCommands.push_back(cmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (CommandList::const_iterator it = lstCommands.begin(); it != lstCommands.end(); it++)
	{
		(*it)->Execute();
	}

	lstCommands.clear();
}

SceneRegistrationBroker::~SceneRegistrationBroker()
{
	DebugMsg::out("Scene Registration Broker destructor\n");
}