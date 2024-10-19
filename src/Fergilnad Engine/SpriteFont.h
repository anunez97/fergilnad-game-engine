// SpriteFont

#ifndef _SpriteFont
#define _SpriteFont

#include <string>
#include <map>
#include <xmllite.h>
#include "AzulCore.h"

class FergilnadSprite;

class SpriteFont
{
public:
	using Key = int;
	using Glyph = FergilnadSprite;

private:
	std::string Name;
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

public:
	SpriteFont() = delete;
	SpriteFont(std::string path);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	/// <summary>
	/// Gives the glyph for the spritefont
	/// </summary>
	/// <param name="c">Character for the glyph wanted</param>
	/// <returns></returns>
	Glyph* GetGlyph(char c);
};

#endif _SpriteFont