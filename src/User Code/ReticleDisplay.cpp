// Reticle Display

#include "ReticleDisplay.h"

#include "SpriteFontManager.h"

ReticleDisplay::ReticleDisplay()
	:posx(130), posy(0), pDisplay(0)
{

}

ReticleDisplay::~ReticleDisplay()
{
	delete pDisplay;
}

void ReticleDisplay::Initialize()
{
	pFont = SpriteFontManager::Get("Arial15");

	pDisplay = new SpriteString();

	pDisplay->Set(pFont, "Health: 100", posx, posy);
}

void ReticleDisplay::Render()
{
	pDisplay->Render();
}

void ReticleDisplay::SetPosition(int x, int y)
{
	posx = x;
	posy = y;

	pDisplay->Set(x, y);
}