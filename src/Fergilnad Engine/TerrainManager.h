// Terrain Manager

#ifndef _TerrainManager
#define _TerrainManager

#include "AzulCore.h"
#include <map>

#include "Terrain.h"

class TerrainManager
{
	friend class TerrainManagerAttorney;

private:
	static TerrainManager* ptrInstance;

	static TerrainManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TerrainManager();
		return *ptrInstance;
	}

	TerrainManager();
	TerrainManager(const TerrainManager& other) = delete;
	TerrainManager& operator=(const TerrainManager& other) = delete;
	~TerrainManager() = default;

	void privLoad(const std::string key, const char* path, int sidelen, float maxheight, float zeroalt, std::string texkey, float urepeat, float vrepeat);

	Terrain* privGet(const std::string key);

	void privDelete();
	static void Delete() { Instance().privDelete(); }

	std::map<std::string, Terrain*> terrainMap;
	std::string DefaultPath;

public:
	/// <summary>
	/// Loads a model file into the Model Manager.
	/// </summary>
	/// <param name="key"> Key used to refer to the specific model. </param>
	/// <param name="path"> Path to the model file.  File must be a .azul file. Path includes filename with file extension, i.e. "tank.azul".</param>
	static void Load(const std::string key, const char* path, int sidelen, float maxheight, float zeroalt, std::string texkey, float urepeat, float vrepeat) 
	{ 
		Instance().privLoad(key, path, sidelen, maxheight, zeroalt, texkey, urepeat, vrepeat); 
	}

	/// <summary>
	/// Method that returns a Model object
	/// </summary>
	/// <param name="key"> Refers to the specific model. </param>
	/// <returns> Pointer to Model object. </returns>
	static Terrain* Get(const std::string key) { return Instance().privGet(key); }
};

#endif _TerrainManager