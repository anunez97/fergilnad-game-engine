// Scene Registration Command

#ifndef _SceneRegistrationCommand
#define _SceneRegistrationCommand

#include "CommandBase.h"

class SceneRegistrationCommand : public CommandBase
{
public:
	SceneRegistrationCommand() {};
	SceneRegistrationCommand(const SceneRegistrationCommand& other) = delete;
	SceneRegistrationCommand& operator=(const SceneRegistrationCommand& other) = delete;
	virtual ~SceneRegistrationCommand() {};

};

#endif _SceneRegistrationCommand