// Level CompleteDisplay

#include "LevelCompleteDisplay.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "Fergilnad.h"

LevelCompleteDisplay::LevelCompleteDisplay()
	:posx(0), posy(Fergilnad::GetHeight() / 2)
{
	pFont = SpriteFontManager::Get("Arial30");

	pDisplay = new SpriteString();

	SubmitDrawRegistration();
}

LevelCompleteDisplay::~LevelCompleteDisplay()
{
	delete pDisplay;
}

void LevelCompleteDisplay::Draw2D()
{
	pDisplay->Set(pFont, "Press Space to Continue", posx, posy);
	pDisplay->Render();
}