// Terrain Manager

#include "TerrainManager.h"

TerrainManager* TerrainManager::ptrInstance = nullptr;

TerrainManager::TerrainManager()
	:DefaultPath((std::string)"Textures/")
{
}

void TerrainManager::privLoad(const std::string key, const char* path, int sidelen, float maxheight, float zeroalt, std::string texkey, float urepeat, float vrepeat)
{
	// check if key isn't used already
	if (terrainMap.count(key))
	{
		DebugMsg::out("ERROR Model Manager: Model key '%s' already in use.\n", key.c_str());
		assert(false && "Model key already used");
	}

	// add the default path
	std::string strpath = DefaultPath + path;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	terrainMap[key] = new Terrain(newpath, sidelen, maxheight, zeroalt, texkey, urepeat, vrepeat);

	delete newpath;
}

Terrain* TerrainManager::privGet(const std::string key)
{
	// if the key doesn't exist, crash
	if (terrainMap.count(key) == 0)
	{
		DebugMsg::out("ERROR Model Manager: Model key '%s' not in use.\n", key.c_str());
		assert(false && "Model key doesn't exist");
	}

	return terrainMap[key];
}

void TerrainManager::privDelete()
{
	// clear the map
	for (std::map<std::string, Terrain*>::iterator it = terrainMap.begin(); it != terrainMap.end(); it++)
	{
		delete it->second;
	}

	// Terminate the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}