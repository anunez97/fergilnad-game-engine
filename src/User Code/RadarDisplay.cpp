// Radar Display

#include "RadarDisplay.h"

#include "SpriteFontManager.h"

RadarDisplay::RadarDisplay()
	:posx(130), posy(0), pDisplay(0)
{

}

RadarDisplay::~RadarDisplay()
{
	delete pDisplay;
}

void RadarDisplay::Initialize()
{
	pFont = SpriteFontManager::Get("Arial15");

	pDisplay = new SpriteString();

	pDisplay->Set(pFont, "RadarDisplay: 10 enemies", posx, posy);
}

void RadarDisplay::Render()
{
	pDisplay->Render();
}

void RadarDisplay::SetPosition(int x, int y)
{
	posx = x;
	posy = y;

	pDisplay->Set(x, y);
}