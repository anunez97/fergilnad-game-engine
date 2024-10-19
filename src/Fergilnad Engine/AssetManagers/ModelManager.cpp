// Model Manager

#include "ModelManager.h"

ModelManager* ModelManager::ptrInstance = nullptr;

ModelManager::ModelManager()
	:DefaultPath((std::string)"..//Assets/Models/")
{
}

void ModelManager::privLoad(const std::string key, const char* path)
{
	// check if key isn't used already
	if (modelMap.count(key))
		throw std::runtime_error("Key already used in the model map");

	// add the default path
	std::string strpath = DefaultPath + path;
	char* newpath = new char[strpath.length() + 1];
	strcpy_s(newpath, strpath.length() + 1, strpath.c_str());

	modelMap[key] = new Model(newpath);

	delete newpath;
}

void ModelManager::privLoad(const std::string key, const Model::PreMadeModels pmm)
{
	// check if key isn't used already
	if (modelMap.count(key))
		throw std::runtime_error("Key already used in the model map");

	modelMap[key] = new Model(pmm);
}

Model* ModelManager::privGet(const std::string key)
{
	// if the key doesn't exist, crash
	if (modelMap.count(key) == 0)
		throw std::runtime_error("Not a valid key in the model map");

	return modelMap[key];
}

void ModelManager::privDelete()
{
	// clear the map
	for (std::map<std::string, Model*>::iterator it = modelMap.begin(); it != modelMap.end(); it++)
	{
		delete it->second;
	}

	// Terminate the singleton
	delete ptrInstance;
	ptrInstance = nullptr;
}