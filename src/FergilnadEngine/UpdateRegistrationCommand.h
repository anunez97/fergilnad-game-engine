// Update Registration Command

#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "SceneRegistrationCommand.h"

class Updatable;

class UpdateRegistrationCommand : public SceneRegistrationCommand
{
public:
	UpdateRegistrationCommand() {};
	UpdateRegistrationCommand(const UpdateRegistrationCommand& other) = default;
	UpdateRegistrationCommand& operator=(const UpdateRegistrationCommand& other) = default;
	~UpdateRegistrationCommand() {};

	UpdateRegistrationCommand(Updatable* up);

	virtual void Execute();

private:
	Updatable* pUp;
};

#endif _UpdateRegistrationCommand