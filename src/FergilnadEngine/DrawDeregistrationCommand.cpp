// Draw Deregistration Command

#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* dr)
	:pDraw(dr)
{
}

void DrawDeregistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneDeregistration(pDraw);
}