// Draw Deregistration Command

#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class DrawDeregistrationCommand : public SceneRegistrationCommand
{
public:
	DrawDeregistrationCommand() {};
	DrawDeregistrationCommand(const DrawDeregistrationCommand& other) = default;
	DrawDeregistrationCommand& operator=(const DrawDeregistrationCommand& other) = default;
	~DrawDeregistrationCommand() {};

	DrawDeregistrationCommand(Drawable* dr);

	virtual void Execute();

private:
	Drawable* pDraw;
};

#endif _DrawDeregistrationCommand