// UpdatableAttorney

#ifndef _UpdatableAttorney
#define _UpdatableAttorney

#include "Updatable.h"

class UpdatableAttorney
{
public:
	class GameLoop
	{
		friend class UpdatableManager;
	private:
		static void Update(Updatable* pMgr) { pMgr->Update(); }
	};

public:
	class Registration
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
	private:
		static void SceneRegistration(Updatable* pMgr) { pMgr->SceneRegistration(); }
		static void SceneDeregistration(Updatable* pMgr) { pMgr->SceneDeregistration(); }
	};
};

#endif _UpdatableAttorney