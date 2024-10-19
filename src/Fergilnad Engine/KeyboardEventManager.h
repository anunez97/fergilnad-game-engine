// Keyboard Event Manager

#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include "AzulCore.h"
#include "InputEventType.h"
#include <map>
#include "SingleKeyEventManager.h"

class Inputable;

class KeyboardEventManager
{
	friend class KeyboardEventAttorney;

private:
	KeyboardEventManager(const KeyboardEventManager& other) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager& other) = delete;

	using MapKeyManager = std::map<AZUL_KEY, SingleKeyEventManager*>;
	MapKeyManager mapKeyManagers;

public:
	KeyboardEventManager();
	~KeyboardEventManager();

	/// <summary>
	/// Registers the Inputable to check for a key press/release
	/// </summary>
	/// <param name="in">Pointer to the Inputable</param>
	/// <param name="k">The key to be checked</param>
	/// <param name="e">The specific key event being checked for; pressed or released</param>
	/// <param name="ref">Entry reference to the map</param>
	void Register(Inputable* in, AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef& ref);
	void Deregister(AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef ref);

	void ProcessKeyEvents();

};

#endif _KeyboardEventManager