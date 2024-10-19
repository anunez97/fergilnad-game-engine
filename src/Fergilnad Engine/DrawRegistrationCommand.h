// Draw Registration Command

#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class DrawRegistrationCommand : public SceneRegistrationCommand
{
public:
	DrawRegistrationCommand() {};
	DrawRegistrationCommand(const DrawRegistrationCommand& other) = default;
	DrawRegistrationCommand& operator=(const DrawRegistrationCommand& other) = default;
	~DrawRegistrationCommand() {};

	DrawRegistrationCommand(Drawable* dr);

	virtual void Execute();

private:
	Drawable* pDraw;
};

#endif _DrawRegistrationCommand