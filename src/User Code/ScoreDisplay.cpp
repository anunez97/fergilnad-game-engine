// Score Display

#include "ScoreDisplay.h"
#include "SpriteFontManager.h"
#include "SpriteFont.h"
#include "SpriteString.h"

ScoreDisplay::ScoreDisplay()
	:posx(130), posy(0), pDisplay(0)
{
	
}

ScoreDisplay::~ScoreDisplay()
{
	delete pDisplay;
}

void ScoreDisplay::Initialize()
{
	pFont = SpriteFontManager::Get("Arial30");

	pDisplay = new SpriteString();

	pDisplay->Set(pFont, "Score:    0", posx, posy);
}

void ScoreDisplay::SetPosition(int x, int y)
{
	posx = x;
	posy = y;

	pDisplay->Set(x, y);
}

void ScoreDisplay::SetScore(int score)
{
	pDisplay->Set(pFont, "Score: " + std::to_string(score), posx, posy);
}

void ScoreDisplay::Render()
{
	pDisplay->Render();
}