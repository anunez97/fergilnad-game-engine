// Shader Manager

#ifndef _ShaderManager
#define _ShaderManager

#include <map>
#include "AzulCore.h"

class ShaderManager
{
	friend class ShaderManagerAttorney;

private:
	// Singleton
	static ShaderManager* ptrInstance;

	static ShaderManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ShaderManager;
		return *ptrInstance;
	}

	ShaderManager();
	ShaderManager(const ShaderManager& other) = delete;
	ShaderManager& operator=(const ShaderManager& other) = delete;
	~ShaderManager() = default;

	void privLoad(const std::string key, const char* path);
	ShaderObject* privGet(const std::string key);
	void privDelete();
	static void Delete() { Instance().privDelete(); }

	std::map<std::string, ShaderObject*> shaderMap;
	const std::string DefaultPath;

public:
	/// <summary>
	/// Loads a shader object into the Shader Manager.
	/// </summary>
	/// <param name="key"> Refers to the specific ShaderObject in the manager. </param>
	/// <param name="path"> File name of the ShaderObject.  Must be a .glsl file.  Path is just filename with no extension, i.e. "textureFlatRender".</param>
	static void Load(const std::string key, const char* path) { Instance().privLoad(key, path); }

	/// <summary>
	/// Gets a ShaderObject from the manager.
	/// </summary>
	/// <param name="key"> Refers to the specific ShaderObject. </param>
	/// <returns> Returns a ShaderObject pointer. </returns>
	static ShaderObject* Get(std::string key) { return Instance().privGet(key); }
};

#endif _ShaderManager