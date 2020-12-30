// Objective Display

#include "ObjectiveDisplay.h"

#include "SpriteFontManager.h"
#include "Fergilnad.h"

ObjectiveDisplay::ObjectiveDisplay()
	:posx(0), posy(Fergilnad::GetHeight()), pDisplay(0)
{

}

ObjectiveDisplay::~ObjectiveDisplay()
{
	delete pDisplay;
}

void ObjectiveDisplay::Initialize()
{
	pFont = SpriteFontManager::Get("Arial15");

	pDisplay = new SpriteString();

	pDisplay->Set(pFont, "Objective Text", posx, posy);
}

void ObjectiveDisplay::Render()
{
	pDisplay->Render();
}

void ObjectiveDisplay::SetPosition(int x, int y)
{
	posx = x;
	posy = y;

	pDisplay->Set(x, y);
}

int ObjectiveDisplay::GetHeight()
{
	return pDisplay->GetHeight();
}