// Input Registration Command

#include "InputRegistrationCommand.h"
#include "InputableAttorney.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* in)
	:pIn(in)
{
}

void InputRegistrationCommand::SetEvent(InputEventType e)
{
	ev = e;
}

void InputRegistrationCommand::SetKey(AZUL_KEY k)
{
	key = k;
}

void InputRegistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneRegistration(pIn, key, ev);
}