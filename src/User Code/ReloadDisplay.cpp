// Reload Display

#include "ReloadDisplay.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "PlayerManager.h"

ReloadDisplay::ReloadDisplay()
	:posx(5), posy(0), pDisplay(0)
{
}

ReloadDisplay::~ReloadDisplay()
{
	delete pDisplay;
}

void ReloadDisplay::Initialize()
{
	pFont = SpriteFontManager::Get("Arial30");
	pDisplay = new SpriteString();

	pDisplay->Set(pFont, "READY", posx, posy);
}

void ReloadDisplay::SetPosition(int x, int y)
{
	posx = x;
	posy = y;

	pDisplay->Set(x, y);
}

void ReloadDisplay::Reloading()
{
	pDisplay->Set(pFont, std::to_string(PlayerManager::GetReloadPercent()) + "%", posx, posy);
}

void ReloadDisplay::ReadyToFire()
{
	pDisplay->Set(pFont, "READY", posx, posy);
}

void ReloadDisplay::UpdateDisplay()
{
	if (PlayerManager::GetReloadPercent() == 0)
		ReadyToFire();
	else
		Reloading();
}

void ReloadDisplay::Render()
{
	pDisplay->Render();
}