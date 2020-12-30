// Update Deregistration Command

#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Updatable;

class UpdateDeregistrationCommand : public SceneRegistrationCommand
{
public:
	UpdateDeregistrationCommand() = default;
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand& other) = default;
	UpdateDeregistrationCommand& operator=(const UpdateDeregistrationCommand& other) = default;
	~UpdateDeregistrationCommand() = default;

	UpdateDeregistrationCommand(Updatable* up);

	virtual void Execute();

private:
	Updatable* pUp;
};

#endif _UpdateRegistrationCommand