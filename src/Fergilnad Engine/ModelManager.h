// Model Manager

#ifndef _ModelManager
#define _ModelManager

#include <map>
#include "AzulCore.h"

class ModelManager
{
	friend class ModelManagerAttorney;

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
	void privLoad(const std::string key, const int size, const int repeatX, const int repeatZ);

	Model* privGet(const std::string key);
	void privDelete();
	static void Delete() { Instance().privDelete(); }

	std::map<std::string, Model*> modelMap;
	std::string DefaultPath;

public:
	/// <summary>
	/// Loads a model file into the Model Manager.
	/// </summary>
	/// <param name="key"> Key used to refer to the specific model. </param>
	/// <param name="path"> Path to the model file.  File must be a .azul file. Path includes filename with file extension, i.e. "tank.azul".</param>
	static void Load(const std::string key, const char* path) { Instance().privLoad(key, path); }

	/// <summary>
	/// Loads a premade model into the Model Manager.
	/// </summary>
	/// <param name="key"> Key used to refer to the specific model. </param>
	/// <param name="pmm"> Premade model. </param>
	static void Load(const std::string key, const Model::PreMadeModels pmm) { Instance().privLoad(key, pmm); }

	/// <summary>
	/// Loads a custom plane with repeated textures
	/// </summary>
	/// <param name="key"> Key used to refer to the specific model. </param>
	/// <param name="pmm"> Premade model. </param>
	static void Load(const std::string key, const int size, const int repeatX, const int repeatZ) { Instance().privLoad(key, size, repeatX, repeatZ); }

	/// <summary>
	/// Method that returns a Model object
	/// </summary>
	/// <param name="key"> Refers to the specific model. </param>
	/// <returns> Pointer to Model object. </returns>
	static Model* Get(const std::string key) { return Instance().privGet(key); }
};

#endif _ModelManager