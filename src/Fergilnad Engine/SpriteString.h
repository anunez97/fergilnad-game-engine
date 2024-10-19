// Sprite String

#ifndef _SpriteString
#define _SpriteString

#include "SpriteFont.h"
#include <vector>

class SpriteString
{
public:
	SpriteString() = default;
	SpriteString(const SpriteString& other) = delete;
	SpriteString& operator=(const SpriteString& other) = delete;
	~SpriteString();

	SpriteString(SpriteFont* sf, std::string s, int x, int y);

	/// <summary>
	/// Renders the SpriteString.
	/// </summary>
	void Render();

	/// <summary>
	/// Sets the SpriteString's font, string, and position
	/// </summary>
	/// <param name="sf"> Pointer to SpriteFont. </param>
	/// <param name="s"> String </param>
	/// <param name="x"> X Position </param>
	/// <param name="y"> Y Position </param>
	void Set(SpriteFont* sf, std::string s, int x, int y);

	/// <summary>
	/// Sets the SpriteString's position
	/// </summary>
	/// <param name="x"> X Position </param>
	/// <param name="y"> Y Postiion </param>
	void Set(int x, int y);

	/// <summary>
	/// Gets the SpriteString's width
	/// </summary>
	/// <returns> SpriteString's width as an int. </returns>
	int GetWidth();

	/// <summary>
	/// Gets the SpriteString's height
	/// </summary>
	/// <returns> SpriteString's height as an int. </returns>
	int GetHeight();
	

private:
	using GlyphCollection = std::vector<SpriteFont::Glyph*>;
	GlyphCollection glyphs;

	int width;
	int height;
	int posx;
	int posy;

};

#endif _SpriteString