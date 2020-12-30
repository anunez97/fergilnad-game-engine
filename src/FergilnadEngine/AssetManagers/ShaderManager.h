// Shader Manager

#ifndef _ShaderManager
#define _ShaderManager

#include <map>
#include "AzulCore.h"

class ShaderManager
{
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

	std::map<std::string, ShaderObject*> shaderMap;
	const std::string DefaultPath;

public:
	static void Load(const std::string key, const char* path) { Instance().privLoad(key, path); }
	static ShaderObject* Get(std::string key) { return Instance().privGet(key); }

	static void Delete() { Instance().privDelete(); }
};

#endif _ShaderManager