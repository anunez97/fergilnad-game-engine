// Health Display

#include "HealthDisplay.h"

#include "SpriteFontManager.h"

HealthDisplay::HealthDisplay()
	:posx(130), posy(0), pDisplay(0)
{

}

HealthDisplay::~HealthDisplay()
{
	delete pDisplay;
}

void HealthDisplay::Initialize()
{
	pFont = SpriteFontManager::Get("Arial15");

	pDisplay = new SpriteString();

	pDisplay->Set(pFont, "Health: 100", posx, posy);
}

void HealthDisplay::Render()
{
	pDisplay->Render();
}

void HealthDisplay::SetPosition(int x, int y)
{
	posx = x;
	posy = y;

	pDisplay->Set(x, y);
}

int HealthDisplay::GetWidth()
{
	return pDisplay->GetWidth();
}

int HealthDisplay::GetHeight()
{
	return pDisplay->GetHeight();
}