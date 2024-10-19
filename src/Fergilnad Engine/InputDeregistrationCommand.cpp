// Input Deregistration Command

#include "InputDeregistrationCommand.h"
#include "InputableAttorney.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* in)
	:pIn(in)
{
}

void InputDeregistrationCommand::SetEvent(InputEventType e)
{
	ev = e;
}

void InputDeregistrationCommand::SetKey(AZUL_KEY k)
{
	key = k;
}

void InputDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneDeregistration(pIn, key, ev);
}