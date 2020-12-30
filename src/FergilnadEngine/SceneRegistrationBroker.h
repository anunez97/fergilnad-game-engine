// Scene Registration Broker

#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <list>
#include "AzulCore.h"

class CommandBase;

class SceneRegistrationBroker
{
public:
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker& other) = delete;
	SceneRegistrationBroker& operator=(const SceneRegistrationBroker& other) = delete;
	~SceneRegistrationBroker();

	void addCommand(CommandBase* c);
	void ExecuteCommands();

private:
	using CommandList = std::list<CommandBase*>;
	CommandList lstCommands;

};

#endif _SceneRegistrationBroker
