// Image Manager

#include "ImageManager.h"

ImageManager* ImageManager::ptrInstance = nullptr;

ImageManager::ImageManager()
	:DefaultPath((std::string)"..//Assets/Images/")
{
}

void ImageManager::privLoad(const std::string& key, Texture* tex)
{
	// check if key isn't used already
	if (imageMap.count(key))
	{
		DebugMsg::out("ERROR Image Manager: Image key '%s' already in use.\n", key.c_str());
		assert(false && "Image key already used");
	}

	// add the default path
	std::string strpath = DefaultPath + key;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	imageMap[key] = new Image(tex, new Rect(0.0f, 0.0f, static_cast<float>(tex->getWidth()), static_cast<float>(tex->getHeight())));

	delete newpath;
}

void ImageManager::privLoad(const std::string& key, Texture* tex, Rect* r)
{
	// check if key isn't used already
	if (imageMap.count(key))
	{
		DebugMsg::out("ERROR Image Manager: Image key '%s' already in use.\n", key.c_str());
		assert(false && "Image key already used");
	}

	// add the default path
	std::string strpath = DefaultPath + key;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	imageMap[key] = new Image(tex, r);

	delete newpath;
}

Image* ImageManager::Get(const std::string& key)
{
	// if the key doesn't exist, crash
	if (Instance().imageMap.count(key) == 0)
	{
		DebugMsg::out("ERROR Image Manager: Image key '%s' not in use.\n", key.c_str());
		assert(false && "Image key doesn't exist");
	}

	return Instance().imageMap[key];
}

void ImageManager::privDelete()
{
	// clear the map
	for (std::map<std::string, Image*>::iterator it = imageMap.begin(); it != imageMap.end(); it++)
	{
		delete it->second;
	}

	// Terminate the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}