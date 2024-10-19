// Keyboard Event Manager

#include "KeyboardEventManager.h"

KeyboardEventManager::KeyboardEventManager()
{

}

KeyboardEventManager::~KeyboardEventManager()
{
	DebugMsg::out("KeyboardEventManager destructor\n");
	for (std::map<AZUL_KEY, SingleKeyEventManager*>::iterator it = mapKeyManagers.begin(); it != mapKeyManagers.end(); it++)
	{
		delete (*it).second;
	}
}

void KeyboardEventManager::Register(Inputable* in, AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef& ref)
{
	// If there isnt a manager for the key, create one
	if (mapKeyManagers.count(k) == 0)
	{
		SingleKeyEventManager* pSKEM = new SingleKeyEventManager(k);
		pSKEM->Register(in, e, ref);
		mapKeyManagers[k] = pSKEM;
	}
	else
	{
		mapKeyManagers[k]->Register(in, e, ref);
	}
}

void KeyboardEventManager::Deregister(AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef ref)
{
	mapKeyManagers[k]->Deregister(e, ref);
}

void KeyboardEventManager::ProcessKeyEvents()
{
	for (std::map<AZUL_KEY, SingleKeyEventManager*>::iterator it = mapKeyManagers.begin(); it != mapKeyManagers.end(); it++)
	{
		(*it).second->ProcessKeyEvents();
	}
}