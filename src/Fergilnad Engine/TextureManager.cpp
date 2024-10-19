// Texture Manager

#include "TextureManager.h"

TextureManager* TextureManager::ptrInstance = nullptr;

TextureManager::TextureManager()
	:DefaultPath((std::string)"..//Assets/Textures/")
{
}

void TextureManager::privLoad(const std::string key, const char* path)
{
	// check if key isn't used already
	if (textureMap.count(key))
	{
		DebugMsg::out("ERROR Texture Manager: Texture key '%s' already in use.\n", key.c_str());
		assert(false && "Texture key already used");
	}

	// add the default path
	std::string strpath = DefaultPath + path;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	textureMap[key] = new Texture(newpath);
	delete newpath;
}

void TextureManager::privLoad(const std::string key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char& alpha)
{
	// check if key isn't used already
	if (textureMap.count(key))
	{
		DebugMsg::out("ERROR Texture Manager: Texture key '%s' already in use.\n", key.c_str());
		assert(false && "Texture key already used");
	}

	textureMap[key] = new Texture(red, green, blue, alpha);

}

// For SpriteFonts
void TextureManager::privLoad(const std::string key, const std::string path)
{
	// check if key isn't used already
	if (textureMap.count(key))
	{
		DebugMsg::out("ERROR Texture Manager: Texture key '%s' already in use.\n", key.c_str());
		assert(false && "Texture key already used");
	}

	// add the default path
	std::string strpath = DefaultPath + path;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	textureMap[key] = new Texture(newpath);
	delete newpath;
}

Texture* TextureManager::privGet(const std::string key)
{
	// if the key doesn't exist, crash
	if (textureMap.count(key) == 0)
	{
		DebugMsg::out("ERROR Texture Manager: Texture key '%s' not in use.\n", key.c_str());
		assert(false && "Texture key doesn't exist");
	}

	return textureMap[key];
}

void TextureManager::privDelete()
{
	// clear the map
	for (std::map<std::string, Texture*>::iterator it = textureMap.begin(); it != textureMap.end(); it++)
	{
		delete it->second;
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}