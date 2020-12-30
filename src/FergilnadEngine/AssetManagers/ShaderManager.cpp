// Shader Manager

#include "ShaderManager.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderManager::ShaderManager()
	:DefaultPath((std::string)"..//Assets/Shaders/")
{
}

void ShaderManager::privLoad(const std::string key, const char* path)
{
	// check if key isn't used already
	if(shaderMap.count(key))
		throw std::runtime_error("Key already used in the shader map");

	// add the default path
	std::string strpath = DefaultPath + path;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	shaderMap[key] = new ShaderObject(newpath);

	delete newpath;
}

ShaderObject* ShaderManager::privGet(const std::string key)
{
	// if the key doesn't exist, crash
	if (shaderMap.count(key) == 0)
		throw std::runtime_error("Not a valid key in the shader map");
	
	return shaderMap[key];
}

void ShaderManager::privDelete()
{
	// clear the map
	for (std::map<std::string, ShaderObject*>::iterator it = shaderMap.begin(); it != shaderMap.end(); it++)
	{
		delete it->second;
	}

	// Terminate the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}