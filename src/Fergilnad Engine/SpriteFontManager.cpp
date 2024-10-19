// Sprite Font Manager

#include "SpriteFontManager.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

SpriteFontManager::SpriteFontManager()
	:DefaultPath((std::string)"..//Assets/SpriteFonts/")
{

}

SpriteFontManager::~SpriteFontManager()
{

}

void SpriteFontManager::privLoad(const MapKey& key, const std::string& path)
{
	// check if key isn't used already
	if (storageMap.count(key))
	{
		DebugMsg::out("ERROR SpriteFont Manager: SpriteFont key '%s' already in use.\n", key.c_str());
		assert(false && "SpriteFont key already used");
	}

	// add the default path
	std::string strpath = DefaultPath + path;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	storageMap[key] = new SpriteFont(path);
	delete newpath;
}

SpriteFont* SpriteFontManager::Get(const MapKey& key)
{
	// if the key doesn't exist, crash
	if (Instance().storageMap.count(key) == 0)
	{
		DebugMsg::out("ERROR SpriteFont Manager: SpriteFont key '%s' not in use.\n", key.c_str());
		assert(false && "SprintFont key doesn't exist");
	}

	return Instance().storageMap[key];
}

void SpriteFontManager::privDelete()
{
	for (StorageMap::iterator it = storageMap.begin(); it != storageMap.end(); it++)
	{
		delete (*it).second;
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}