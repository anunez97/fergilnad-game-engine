// Model Manager

#ifndef _ModelManager
#define _ModelManager

#include <map>
#include "AzulCore.h"

class ModelManager
{
private:
	static ModelManager* ptrInstance;

	static ModelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ModelManager;
		return *ptrInstance;
	}

	ModelManager();
	ModelManager(const ModelManager& other) = delete;
	ModelManager& operator=(const ModelManager& other) = delete;
	~ModelManager() = default;

	void privLoad(const std::string key, const char* path);
	void privLoad(const std::string key, const Model::PreMadeModels pmm);
	Model* privGet(const std::string key);
	void privDelete();

	std::map<std::string, Model*> modelMap;
	std::string DefaultPath;

public:
	static void Load(const std::string key, const char* path) { Instance().privLoad(key, path); }
	static void Load(const std::string key, const Model::PreMadeModels pmm) { Instance().privLoad(key, pmm); }
	static Model* Get(const std::string key) { return Instance().privGet(key); }

	static void Delete() { Instance().privDelete(); }

};

#endif _ModelManager