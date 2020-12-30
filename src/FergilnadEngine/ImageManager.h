// Image Manager

#ifndef _ImageManager
#define _ImageManager

#include "AzulCore.h"
#include <map>

class ImageManager
{
	friend class ImageManagerAttorney;

private:
	static ImageManager* ptrInstance;

	static ImageManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ImageManager;
		return *ptrInstance;
	}

	ImageManager();
	ImageManager(const ImageManager& other) = delete; 
	ImageManager& operator=(const ImageManager& other) = delete; 
	~ImageManager() = default;

	void privLoad(const std::string& key, Texture* tex);
	void privLoad(const std::string& key, Texture* tex, Rect* r);
	static void Delete() { Instance().privDelete(); }
	void privDelete();

	std::map<std::string, Image*> imageMap;
	std::string DefaultPath;

public:
	/// <summary>
	/// Loads a texture into the Image Manager.  Primarily used for 2D Sprites.
	/// </summary>
	/// <param name="key"> Key used to refer to the image texture. </param>
	/// <param name="tex"> Texture used by the image.  Must be a .tga file and must be loaded in the Texture Manager.  </param>
	static void Load(const std::string& key, Texture* tex) { Instance().privLoad(key, tex); }

	/// <summary>
	/// Loads a texture into the Image Manager. Primarily used to load spritefonts.
	/// </summary>
	/// <param name="key"> Key used to refer to the image texture. </param>
	/// <param name="tex"> Texture used by the image.  Must be a .tga file. </param>
	/// <param name="r"> Size and position of the section on the texture for the image.  </param>
	static void Load(const std::string& key, Texture* tex, Rect* r) { Instance().privLoad(key, tex, r); }

	/// <summary>
	/// Method gets a specific image from the manager.
	/// </summary>
	/// <param name="key"> Key that refers to specific Image. </param>
	/// <returns> Pointer to Image object. </returns>
	static Image* Get(const std::string& key);
};

#endif _ImageManager