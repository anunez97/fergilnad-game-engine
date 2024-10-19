// Single Key Event Manager

#include "SingleKeyEventManager.h"
#include "Inputable.h"
#include "InputableAttorney.h"

SingleKeyEventManager::~SingleKeyEventManager()
{
	DebugMsg::out("Single Key Event Manager destructor\n");
}

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
	:key(k), currstate(false), prevstate(false)
{
}

void SingleKeyEventManager::Register(Inputable* in, InputEventType e, StorageRef& ref)
{
	switch (e)
	{
	case InputEventType::KEY_PRESS:
		ref = keyPressCol.insert(keyPressCol.end(), in);
		break;
	case InputEventType::KEY_RELEASE:
		ref = keyReleaseCol.insert(keyReleaseCol.end(), in);
		break;
	default:
		DebugMsg::out("Single Key Event Manager Register not working\n");
	}
}

void SingleKeyEventManager::Deregister(InputEventType e, StorageRef ref)
{
	switch (e)
	{
	case InputEventType::KEY_PRESS:
		keyPressCol.erase(ref);
		break;
	case InputEventType::KEY_RELEASE:
		keyReleaseCol.erase(ref);
		break;
	}
}

void SingleKeyEventManager::ProcessKeyEvents()
{
	currstate = Keyboard::GetKeyState(key);

	if (currstate == true && currstate != prevstate)
	{
		// Process Key Presses
		for (std::list<Inputable*>::iterator it = keyPressCol.begin(); it != keyPressCol.end(); it++)
		{
			InputableAttorney::GameLoop::KeyPressed((*it), key);
		}
	}
	else if (currstate == false && currstate != prevstate)
	{
		// Process Key Releases
		for (std::list<Inputable*>::iterator it = keyReleaseCol.begin(); it != keyReleaseCol.end(); it++)
		{
			InputableAttorney::GameLoop::KeyReleased((*it), key);
		}
	}

	prevstate = currstate;
}