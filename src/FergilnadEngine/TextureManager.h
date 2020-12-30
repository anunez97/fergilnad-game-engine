// Texture Manager

#ifndef _TextureManager
#define _TextureManager

#include <map>
#include "AzulCore.h"

class TextureManager
{
	friend class TextureManagerAttorney;

private:
	static TextureManager* ptrInstance;

	static TextureManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TextureManager;
		return *ptrInstance;
	}

	TextureManager();
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	~TextureManager() = default;

	void privLoad(const std::string key, const char* path);
	void privLoad(const std::string key, const std::string path);
	void privLoad(const std::string key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, 
		const unsigned char& alpha);
	Texture* privGet(const std::string key);
	void privDelete();
	static void Delete() { Instance().privDelete(); }

	std::map<std::string, Texture*> textureMap;
	std::string DefaultPath;

public:
	/// <summary>
	/// Loads a texture into the Texture Manager.
	/// </summary>
	/// <param name="key"> Refers to the specfic Texture</param>
	/// <param name="path"> Filename of the texture.  Must be a .tga file. Path must be in "<filename>.tga" format.</param>
	static void Load(const std::string key, const char* path) { Instance().privLoad(key, path); }
	static void Load(const std::string key, const std::string path) { Instance().privLoad(key, path); }
	static void Load(const std::string key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char& alpha = 1) { Instance().privLoad(key, red, green, blue, alpha); }
	static Texture* Get(const std::string key) { return Instance().privGet(key); }

};

#endif _TextureManager