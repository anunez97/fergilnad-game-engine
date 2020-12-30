// Updatable Manager

#include "UpdatableManager.h"
#include "UpdatableAttorney.h"

UpdatableManager::~UpdatableManager()
{
	DebugMsg::out("UpdatableManager destroyed\n");
}

void UpdatableManager::Register(Updatable* up, StorageListRef& ref)
{
	ref = storageList.insert(storageList.end(), up);
}

void UpdatableManager::Deregister(StorageListRef ref)
{
	storageList.erase(ref);
}

void UpdatableManager::ProcessElements()
{
	for (std::list<Updatable*>::iterator it = storageList.begin(); it != storageList.end(); it++)
	{
		UpdatableAttorney::GameLoop::Update(*it);
	}
}