// UpdateRegistrationCommand

#include "UpdateRegistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* up)
	:pUp(up)
{
}

void UpdateRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneRegistration(pUp);
}