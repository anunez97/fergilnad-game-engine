// Drawable Manager

#include "DrawableManager.h"
#include "DrawableAttorney.h"

DrawableManager::~DrawableManager()
{
	DebugMsg::out("DrawableManager destroyed\n");
}

void DrawableManager::Register(Drawable* dr, StorageListRef& ref)
{
	ref = storageList.insert(storageList.end(), dr);
}

void DrawableManager::Deregister(StorageListRef ref)
{
	storageList.erase(ref);
}

void DrawableManager::ProcessElements()
{
	for (std::list<Drawable*>::iterator it = storageList.begin(); it != storageList.end(); it++)
	{
		DrawableAttorney::GameLoop::Draw((*it));
	}

	for (std::list<Drawable*>::iterator it = storageList.begin(); it != storageList.end(); it++)
	{
		DrawableAttorney::GameLoop::Draw2D((*it));
	}
}