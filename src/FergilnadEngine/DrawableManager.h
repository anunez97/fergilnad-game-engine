// Drawable Manager

#ifndef _DrawableManager
#define _DrawableManager

#include "AzulCore.h"
#include <list>

class Drawable;

class DrawableManager
{
private:
	using StorageList = std::list<Drawable*>;
	StorageList storageList;

public:
	DrawableManager() = default;
	DrawableManager(const DrawableManager& other) = delete;
	DrawableManager& operator=(const DrawableManager& other) = delete;
	~DrawableManager();
	
	using StorageListRef = StorageList::iterator;

	/// <summary>
	/// Processes any Drawables, rendering them on screen
	/// </summary>
	void ProcessElements();

	/// <summary>
	/// Registers the Drawable to the scene
	/// </summary>
	/// <param name="up">Pointer to the Drawable</param>
	/// <param name="ref">Entry reference to the list the Drawable is in for quick removal</param>
	void Register(Drawable* up, StorageListRef& ref);

	/// <summary>
	/// Deregisters the Drawable from the screen
	/// </summary>
	/// <param name="ref">Entry reference to the list the Drawable is in</param>
	void Deregister(StorageListRef ref);

};

#endif _DrawableManager