// Input Deregistration Command

#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
#include "InputEventType.h"

class Inputable;

class InputDeregistrationCommand : public SceneRegistrationCommand
{
public:
	InputDeregistrationCommand() = default;
	InputDeregistrationCommand(const InputDeregistrationCommand& other) = delete;
	InputDeregistrationCommand& operator=(const InputDeregistrationCommand& other) = delete;
	~InputDeregistrationCommand() {};

	InputDeregistrationCommand(Inputable* in);

	void SetEvent(InputEventType e);
	void SetKey(AZUL_KEY k);

	virtual void Execute();

private:
	Inputable* pIn;
	InputEventType ev;
	AZUL_KEY key;
};

#endif _InputDeregistrationCommand