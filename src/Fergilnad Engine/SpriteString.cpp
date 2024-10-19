// Sprite String

#include "SpriteString.h"
#include "FergilnadSprite.h"
#include "SceneManager.h"
#include "Scene.h"

SpriteString::SpriteString(SpriteFont* sf, std::string s, int x, int y)
	:posx(x), posy(y)
{
	SpriteFont::Glyph* g;

	width = static_cast<int>(sf->GetGlyph(' ')->GetWidth());
	height = static_cast<int>(sf->GetGlyph(' ')->GetHeight());

	for (size_t i = 0; i < s.length(); i++)
	{
		g = sf->GetGlyph(s[i]);
		g->SetCenter(g->GetWidth() / 2.0f, g->GetHeight() / 2.0f);
		glyphs.push_back(g);
	}
}

SpriteString::~SpriteString()
{

}

void SpriteString::Render()
{
	float x = static_cast<float>(posx);
	float y = static_cast<float>(posy);

	for (size_t i = 0; i < glyphs.size(); i++)
	{
		glyphs[i]->SetPosition(x, y);
		x += glyphs[i]->GetWidth();
		glyphs[i]->Render(SceneManager::GetCurrentScene()->GetCurrent2DCamera());
	}
}

void SpriteString::Set(SpriteFont* sf, std::string s, int x, int y)
{
	glyphs.clear();

	posx = x;
	posy = y;

	width = static_cast<int>(sf->GetGlyph(' ')->GetWidth());
	height = static_cast<int>(sf->GetGlyph(' ')->GetHeight());

	SpriteFont::Glyph* g;

	for (size_t i = 0; i < s.length(); i++)
	{
		g = sf->GetGlyph(s[i]);
		g->SetCenter(g->GetWidth() / 2.0f, g->GetHeight() / 2.0f);
		glyphs.push_back(g);
	}
}

void SpriteString::Set(int x, int y)
{
	posx = x;
	posy = y;
}

int SpriteString::GetHeight()
{
	return height;
}

int SpriteString::GetWidth()
{
	return width;
}