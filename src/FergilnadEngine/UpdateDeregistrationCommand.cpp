// Update Deregistration Command

#include "UpdateDeregistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* up)
	:pUp(up)
{
}

void UpdateDeregistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneDeregistration(pUp);
}