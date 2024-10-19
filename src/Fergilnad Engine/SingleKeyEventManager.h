// Single Key Event Manager

#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include "AzulCore.h"
#include <list>
#include "InputEventType.h"

class Inputable;

class SingleKeyEventManager
{
	friend class SingleKeyEventAttorney;
private:
	using InputableCollection = std::list<Inputable*>;

public:
	~SingleKeyEventManager();
	SingleKeyEventManager(AZUL_KEY k);

	using StorageRef = InputableCollection::iterator;

	/// <summary>
	/// Registers the key event to the scene
	/// </summary>
	/// <param name="in">Pointer to the Inputable</param>
	/// <param name="e">The input type to be tested for</param>
	/// <param name="ref">Entry reference to the list that will contain the Inputable</param>
	void Register(Inputable* in, InputEventType e, StorageRef& ref);

	/// <summary>
	/// Deregisters the Inputable from the scene
	/// </summary>
	/// <param name="e">The specific input type</param>
	/// <param name="ref">Entry reference to the list that contains the Inputable</param>
	void Deregister(InputEventType e, StorageRef ref);

	/// <summary>
	/// Processes any key events 
	/// </summary>
	void ProcessKeyEvents();

private:
	SingleKeyEventManager() = default;
	SingleKeyEventManager(const SingleKeyEventManager& other) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager& other) = delete;

	InputableCollection keyPressCol;
	InputableCollection keyReleaseCol;
	AZUL_KEY key;
	bool prevstate;
	bool currstate;

};

#endif _SingleKeyEventManager