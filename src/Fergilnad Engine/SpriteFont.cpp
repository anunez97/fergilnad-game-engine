
#include "SpriteFont.h"
#include "TextureManager.h"
#include "FergilnadSprite.h"
#include "ImageManager.h"

#include <xmllite.h>
#include <shlwapi.h>

//*********************************************************
// Don't forget to add the associated libs to your project 
// Properties/Linker/Input  -> add these
//		xmllite.lib
//		shlwapi.lib
//*********************************************************

SpriteFont::SpriteFont(std::string path)
{
	// <Load associate texture into TextureManager>
	Name = path;
	TextureManager::Load(path, path + ".tga");

	// Parse associated XML file
	XMLtoCollection("..//Assets/SpriteFonts/" + path + ".xml");
}

SpriteFont::~SpriteFont()
{
	// to be completed
	for (FontMap::iterator it = fontmap.begin(); it != fontmap.end(); it++)
	{
		delete (*it).second;
	}
}

void SpriteFont::XMLtoCollection(std::string filename)
{
	IXmlReader* reader = nullptr;
	IStream* readStream = nullptr;
	XmlNodeType nodeType;

	CreateXmlReader(IID_PPV_ARGS(&reader), nullptr);

	SHCreateStreamOnFile(filename.c_str(), STGM_READ, &readStream);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(readStream);

	const wchar_t* stringValue = nullptr;
	unsigned int stringSize = 0;

	int key = 0;	// ASCII value
	int x = 0;		// x, y position of the glyph in texture
	int y = 0;
	int w = 0;		// width and height of the gluth in texture
	int h = 0;

	while (S_OK == reader->Read(&nodeType))
	{
		switch (nodeType)
		{
		case XmlNodeType::XmlNodeType_Element:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);

			if (wcscmp(stringValue, L"character") == 0)
			{
				//Gets ASCII value
				reader->MoveToAttributeByName(L"key", nullptr);
				reader->GetValue(&stringValue, &stringSize);
				key = _wtoi(stringValue);
			}
			else if (wcscmp(stringValue, L"x") == 0)
			{
				ElementTextToInt(reader, x);
			}
			else if (wcscmp(stringValue, L"y") == 0)
			{
				ElementTextToInt(reader, y);
			}
			else if (wcscmp(stringValue, L"width") == 0)
			{
				ElementTextToInt(reader, w);
			}
			else if (wcscmp(stringValue, L"height") == 0)
			{
				ElementTextToInt(reader, h);
			}
			else
			{
			}
		} break;

		case XmlNodeType::XmlNodeType_EndElement:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);
			assert(stringValue);

			//If we are at the end of "character", we found everything we need for this char
			if (wcscmp(stringValue, L"character") == 0)
			{
				//************************************************************************
				// You now have all the data for a character: key, x, y, w, h
				//
				// Load the associated image in the ImageManager 
				// (its name could be <font name><key> to insure uniqueness)
				//
				// Create the glyph and add it to the fontmap
				// NB: Consider moving the glyph's origin to the *upper-left* corner...
				//*************************************************************************

				DebugMsg::out("Font %s: creating glyph for ASCII %i\n", Name.c_str(), key);

				ImageManager::Load(Name + std::to_string(key), TextureManager::Get(Name), new Rect(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)));

				FergilnadSprite* glyph = new FergilnadSprite(Name + std::to_string(key));
				glyph->SetCenter(0, glyph->GetHeight());

				fontmap[key] = glyph;
			}

		} break;

		//Don't care about these
		case XmlNodeType::XmlNodeType_Attribute:
		case XmlNodeType::XmlNodeType_CDATA:
		case XmlNodeType::XmlNodeType_Comment:
		case XmlNodeType::XmlNodeType_DocumentType:
		case XmlNodeType::XmlNodeType_None:
		case XmlNodeType::XmlNodeType_ProcessingInstruction:
		case XmlNodeType::XmlNodeType_Text:
		case XmlNodeType::XmlNodeType_Whitespace:
		case XmlNodeType::_XmlNodeType_Last:
		default:
		{} break;
		}
	}

	//Release COM objects
	if (readStream)
	{
		readStream->Release();
	}

	if (reader)
	{
		reader->Release();
	}
}

void SpriteFont::ElementTextToInt(IXmlReader* pReader, int& out)
{
	const wchar_t* stringValue = nullptr;
	UINT stringSize = 0;
	XmlNodeType nodeType;

	while (S_OK == pReader->Read(&nodeType))
	{
		if (nodeType == XmlNodeType::XmlNodeType_Text)
		{
			pReader->GetValue(&stringValue, &stringSize);
			assert(stringValue);

			out = _wtoi(stringValue);
			break;
		}
	}
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char c)
{
	if (c == 9)
		return fontmap[32];

	return fontmap[c];
}


