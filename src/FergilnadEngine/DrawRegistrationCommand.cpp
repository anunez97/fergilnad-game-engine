// Draw Registration Command

#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* dr)
	:pDraw(dr)
{
}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneRegistration(pDraw);
}