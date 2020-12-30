// Input Registration Command

#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
#include "InputEventType.h"

class Inputable;

class InputRegistrationCommand : public SceneRegistrationCommand
{
public:
	InputRegistrationCommand() = default;
	InputRegistrationCommand(const InputRegistrationCommand& other) = delete;
	InputRegistrationCommand& operator=(const InputRegistrationCommand& other) = delete;
	~InputRegistrationCommand() {};

	InputRegistrationCommand(Inputable* in);

	void SetEvent(InputEventType e);
	void SetKey(AZUL_KEY k);
	virtual void Execute();

private:
	Inputable* pIn;
	AZUL_KEY key;
	InputEventType ev;

};

#endif _InputRegistrationCommand