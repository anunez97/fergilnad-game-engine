// Sprite Font Manager

#ifndef _SpriteFontManager
#define _SpriteFontManager

#include "AzulCore.h"
#include <map>

class SpriteFont;

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;

private:
	static SpriteFontManager* ptrInstance;

	static SpriteFontManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpriteFontManager;
		return *ptrInstance;
	}

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager& other) = delete;
	SpriteFontManager& operator=(const SpriteFontManager& other) = delete;
	~SpriteFontManager();

	using MapKey = std::string;
	using StorageMap = std::map<MapKey, SpriteFont*>;
	StorageMap storageMap;

	void privLoad(const MapKey& key, const std::string& path);
	void privDelete();

	static void Delete() { Instance().privDelete(); }

	std::string DefaultPath;

public:
	/// <summary>
	/// Loads a SpriteFont to the manager.
	/// </summary>
	/// <param name="key"> Refers to the specific SpriteFont. </param>
	/// <param name="path"> Filename of the SpriteFont file.  Path is just the filename with no file extensions, i.e. "Arial30".  There must be a .tga file and .xml file of the same name. </param>
	static void Load(const MapKey& key, const std::string& path) { Instance().privLoad(key, path); }

	/// <summary>
	/// Gets a SpriteFont from the manager.
	/// </summary>
	/// <param name="key"> Refers to the specific SpriteFont. </param>
	/// <returns> Returns a pointer to the SpriteFont. </returns>
	static SpriteFont* Get(const MapKey& key);

};

#endif _SpriteFontManager