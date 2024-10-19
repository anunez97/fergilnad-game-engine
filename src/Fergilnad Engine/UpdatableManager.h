// Updatable Manager

#ifndef _UpdatableManager
#define _UpdatableManager

#include <list>
#include "AzulCore.h"

class Updatable;

class UpdatableManager
{
private:
	using StorageList = std::list<Updatable*>;
	StorageList storageList;

public:
	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager& other) = delete;
	UpdatableManager& operator=(const UpdatableManager& other) = delete;
	~UpdatableManager();

	using StorageListRef = StorageList::iterator;

	/// <summary>
	/// Processes the Updatables; calling their Update() method
	/// </summary>
	void ProcessElements();

	/// <summary>
	/// Registers the Updatable to the scene
	/// </summary>
	/// <param name="up">Pointer to the Updatable</param>
	/// <param name="ref">Entry reference to the list that contains the Updatable</param>
	void Register(Updatable* up, StorageListRef& ref);

	/// <summary>
	/// Deregisters the Updatable from the scene
	/// </summary>
	/// <param name="ref">Entry reference to the list that contains the Updatable</param>
	void Deregister(StorageListRef ref);
};

#endif _UpdatableManager